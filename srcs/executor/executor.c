/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/03/04 17:56:24 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void     launch_commands(const t_tree *const node, const int8_t prev_type, int16_t fds[5]);
static void     launch_builtin_cmd(const t_tree *const node, const int8_t prev_type, int16_t fds[5]);
static void     launch_standard_cmd(const t_tree *const node, const int8_t prev_type, int16_t fds[5]);
static t_tree   *skip_till_semicolon(const t_tree *const node);
static void     child(const t_tree *const node, const int16_t fds[5], const int8_t prev_type);
static void     parent(const t_tree *const node, int16_t fds[5], const pid_t pid);
static void     wait_for_children(const t_tree *const node);
static uint16_t get_n_pipelines(const t_tree *const node);

void    executor(const t_tree *const parsed_params)
{
    const uint8_t   original_status = g_status;
    uint8_t         heredoc_status;
    int16_t         fds[5] = {-42, -42, -42, -42, -42}; //pipe read, pipe write, prev_output, original stdin, original stdout

    fds[3] = dup_p(STDIN_FILENO);
    fds[4] = dup_p(STDOUT_FILENO);
    heredoc_status = 0;
    create_heredocs(parsed_params, &heredoc_status);
    dup2_p(fds[3], STDIN_FILENO); //altrimenti se heredoc e' terminato con segnale 130, il comando dopo continua a scrivere nell'fd dell'heredoc
    if (heredoc_status != 0)
    {
        if (heredoc_status == 130)
            g_status = 130;
        return ;
    }
    g_status = (uint8_t)original_status; //fai fallire un comando, fai '<< here echo $?' scrivendo qualsiasi cosa nell heredoc, e vedi che echo $? ritorna l'errore del comando precedente (non 0 anche se heredoc e' stato eseguito correttamente)
    set_signals(S_COMMAND, true);
    launch_commands(parsed_params, -1, fds);
    wait_for_children(parsed_params);
    dup2_p(fds[3], STDIN_FILENO);
}

//Yes, when you use pipes within a subshell, such as in ( cmd1 | cmd2 | cmd3 ), 
//the subshell will wait for the entire pipeline of commands to complete before it returns 
//control to the rest of the script or command line. Each command in the pipeline 
//is executed in parallel in its own sub-process: cmd1's output is piped into
//cmd2, and cmd2's output is piped into cmd3. The subshell waits for the last
//command in the pipeline (cmd3 in this case) to complete, along with 
//all preceding commands in the pipeline, before it finishes.

static void launch_commands(const t_tree *const node, const int8_t prev_type, int16_t fds[5])
{
    t_parser    *elem;
    t_parser    *left_elem;

    if (!node)
        return ; //se e' exit non funziona sleep 2 | ls
    elem = (t_parser *)node->content;
    if (elem->type != CMD)
    {
        left_elem = (t_parser *)node->left->content;
        if (elem->type == PIPELINE)
            pipe_p(fds);
        if (left_elem->cmd && is_builtin(left_elem->cmd->cmd_str))
            launch_builtin_cmd(node, prev_type, fds);
        else
            launch_standard_cmd(node, prev_type, fds);
        if ((elem->type == AND && g_status != 0) || (elem->type == OR && g_status == 0))
            launch_commands(skip_till_semicolon(node), -1, fds);
        else
            launch_commands(node->right, elem->type, fds);
        //signal(SIGPIPE, SIG_DFL);
        return ;
    }
    child(node, fds, prev_type);
}

// Yes, you are correct. When Bash executes built-in commands,
// these commands run directly within the context of the current shell process,
// rather than in a new child process. This means that for a pipeline
// of built-in commands, the commands are executed sequentially, not in parallel
// as they would be if each command in the pipeline were an external command that
// required a new process to be spawned.
static void launch_builtin_cmd(const t_tree *const node, const int8_t prev_type, int16_t fds[5])
{
    const t_parser *const   elem = (t_parser *)node->content;

    if (elem->type == PIPELINE)
    {
        dup2_p(fds[1], STDOUT_FILENO);
        reset_fd(&fds[1]);
    }
    fds[2] = fds[0];
    set_signals(S_COMMAND, true);
    launch_commands(node->left, prev_type, fds);
    dup2_p(fds[4], STDOUT_FILENO);
}

static void launch_standard_cmd(const t_tree *const node, const int8_t prev_type, int16_t fds[5])
{
    const t_parser *const   elem = (t_parser *)node->content;
    const pid_t             pid = fork_p();

    if (pid == 0)
    {
        if (elem->type == PIPELINE)
        {
            dup2_p(fds[1], STDOUT_FILENO);
            reset_fd(&fds[0]);
            reset_fd(&fds[1]);
        }
        set_signals(S_COMMAND, true);
        launch_commands(node->left, prev_type, fds);
        wait_for_children(node->left); //deve stare qua, non su. in questo modo anche le subshells aspettano le pipe al loro interno VEDI SOPRA
        free_data();
        exit(g_status); //lui e' l'unico che deve uscire perche' e' il figlio
    }
    else
        parent(node, fds, pid);
}

static t_tree   *skip_till_semicolon(const t_tree *const node)
{
    t_parser    *elem;

    if (!node)
        return (NULL);
    elem = (t_parser *)node->content;
    if (elem->type == SEMICOLON)
        return (node->right);
    return (skip_till_semicolon(node->right));
}

static void child(const t_tree *const node, const int16_t fds[5], const int8_t prev_type)
{
    const t_parser *const  elem = (t_parser *)node->content;

    if (prev_type == PIPELINE)
        dup2_p(fds[2], STDIN_FILENO);
    replace_env_vars(&elem->cmd->cmd_str, false);
    replace_wildcards(&elem->cmd->cmd_str);
    exec_redirs(elem->cmd->redirs);
    exec(ft_getenv("PATH="), elem->cmd->cmd_str);
}

static void parent(const t_tree *const node, int16_t fds[5], const pid_t pid)
{
    const t_parser *const   elem = (t_parser *)node->content;
    int32_t                 status;

    reset_fd(&fds[1]);
    fds[2] = fds[0];
    if (elem->type != PIPELINE)
    {
        waitpid_p(pid, &status, 0);
        g_status = WEXITSTATUS(status);
        reset_fd(&fds[0]); //se dopo non c'e' pipe chiude la pipeline
        //TODO setenv per _=
    }
}

static void wait_for_children(const t_tree *const node) //aspetta tutti i figli (apparte quelli che erano gia stati aspettati, ovvero ; | || e &&)
{
    int32_t     status;
    uint16_t    n_to_wait;

    n_to_wait = get_n_pipelines(node); //numero di pipeline SULLO STESSO LAYER
    while (n_to_wait--)
    {
        waitpid_p(0, &status, 0);
        g_status = WEXITSTATUS(status);
        //funziona cosi', exit non e' immediato. basta guardare il caso 'sleep 3 && (sleep 2 | exit)'
    }
}

static uint16_t get_n_pipelines(const t_tree *const node)
{
    t_parser    *elem;
    t_parser    *left_elem;
    uint16_t    n;

    n = 0;
    if (!node)
        return (n);
    elem = (t_parser *)node->content;
    if (elem->type == PIPELINE)
    {
        left_elem = (t_parser *)node->left->content;
        if (left_elem->type == CMD && !is_builtin(left_elem->cmd->cmd_str))
            n++;
    }
    n += get_n_pipelines(node->right); //va solo a destra per contare quelle sullo stesso layer
    return (n);
}
