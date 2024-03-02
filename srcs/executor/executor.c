/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 16:47:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void     launch_commands(t_tree *node, int8_t prev_type, int fds[3]);
static void     launch_standard_cmd(t_tree *node, int8_t prev_type, int fds[3]);
static void     launch_builtin_cmd(t_tree *node, int8_t prev_type, int fds[3]);
static void     child(t_tree *node, int fds[3], int8_t prev_type);
static void     parent(t_tree *node, int fds[3], pid_t pid);
static void     wait_for_children(t_tree *node);
static t_tree   *skip_till_semicolon(t_tree *node);
static uint16_t get_n_pipelines(t_tree *node);

//TODO unexpected quit  e messaggio sbagliato con permessi negati a creare file in root 

void    executor(t_tree *parsed_params)
{
    int     original_status;
    int     heredoc_status;
    int     fds[5] = {-42, -42, -42, -42, -42}; //pipe read, pipe write, prev_output, original stdin, original stdout

    fds[3] = dup_p(STDIN_FILENO);
    fds[4] = dup_p(STDOUT_FILENO);
    original_status = g_status;
    heredoc_status = 0;
    create_heredocs(parsed_params, &heredoc_status);
    dup2(fds[3], STDIN_FILENO); //altrimenti se heredoc e' terminato con segnale 130, il comando dopo continua a scrivere nell'fd dell'heredoc
    if (heredoc_status != 0)
    {
        if (heredoc_status == 130)
            g_status = 130;
        return ;
    }
    g_status = original_status; //fai fallire un comando, fai '<< here echo $?' scrivendo qualsiasi cosa nell heredoc, e vedi che echo $? ritorna l'errore del comando precedente (non 0 anche se heredoc e' stato eseguito correttamente)
    set_signals(S_COMMAND, true);
    launch_commands(parsed_params, -1, fds);
    wait_for_children(parsed_params);
    dup2(fds[3], STDIN_FILENO);
}

//Yes, when you use pipes within a subshell, such as in ( cmd1 | cmd2 | cmd3 ), 
//the subshell will wait for the entire pipeline of commands to complete before it returns 
//control to the rest of the script or command line. Each command in the pipeline 
//is executed in parallel in its own sub-process: cmd1's output is piped into
//cmd2, and cmd2's output is piped into cmd3. The subshell waits for the last
//command in the pipeline (cmd3 in this case) to complete, along with 
//all preceding commands in the pipeline, before it finishes.

static void launch_commands(t_tree *node, int8_t prev_type, int fds[3])
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
static void launch_builtin_cmd(t_tree *node, int8_t prev_type, int fds[3])
{
    t_parser    *elem;

    elem = (t_parser *)node->content;
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

static void launch_standard_cmd(t_tree *node, int8_t prev_type, int fds[3])
{
    t_parser    *elem;
    pid_t       pid;

    elem = (t_parser *)node->content;
    pid = fork_p();
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

t_tree   *skip_till_semicolon(t_tree *node)
{
    t_parser    *elem;

    if (!node)
        return (NULL);
    elem = (t_parser *)node->content;
    if (elem->type == SEMICOLON)
        return (node->right);
    return (skip_till_semicolon(node->right));
}

static void child(t_tree *node, int fds[3], int8_t prev_type)
{
    t_parser    *elem;

    elem = (t_parser *)node->content;
    if (prev_type == PIPELINE)
        dup2_p(fds[2], STDIN_FILENO);
    replace_env_vars(&elem->cmd->cmd_str, false);
    replace_wildcards(&elem->cmd->cmd_str);
    exec_redirs(elem->cmd->redirs);
    exec(ft_getenv("PATH="), elem->cmd->cmd_str);
}

static void parent(t_tree *node, int fds[3], pid_t pid)
{
    t_parser    *elem;

    elem = (t_parser *)node->content;
    reset_fd(&fds[1]);
    fds[2] = fds[0];
    if (elem->type != PIPELINE)
    {
        waitpid_p(pid, &g_status, 0);
        g_status = WEXITSTATUS(g_status);
        reset_fd(&fds[0]); //se dopo non c'e' pipe chiude la pipeline
    }
}

void wait_for_children(t_tree *node) //aspetta tutti i figli (apparte quelli che erano gia stati aspettati, ovvero ; | || e &&)
{
    uint16_t    n_to_wait;

    n_to_wait = get_n_pipelines(node); //numero di pipeline SULLO STESSO LAYER
    while (n_to_wait--)
    {
        waitpid_p(0, &g_status, 0);
        g_status = WEXITSTATUS(g_status);
        //funziona cosi', exit non e' immediato. basta guardare il caso 'sleep 3 && (sleep 2 | exit)'
    }
}

static uint16_t get_n_pipelines(t_tree *node)
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
