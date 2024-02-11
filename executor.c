/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/10 23:22:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void     launch_commands(t_tree *node, int8_t prev_type, int fds[3]);
static void     child(t_tree *elem, int fds[3], int8_t prev_type);
static void     parent(pid_t pid, int fds[3], bool is_in_pipeline);
static void     exec_redirs(t_list *redirs);
static void     wait_for_children(t_tree *parsed_params);
static uint32_t count_x(t_tree *node, uint32_t n, int8_t type);

void    executor(t_tree *parsed_params)
{
    int     original_stdin;
    pid_t   pid;
    int     fds[3] = {-42, -42, 42};

    original_stdin = dup_p(STDIN_FILENO);
    create_heredocs(parsed_params);
    if (g_status == 130) //se all'heredoc e' arrivato ctrl+c...
        return ; //...ma comunque non devo eseguire i comandi
    pid = fork_p();
    if (pid == 0)
    {
        set_signals(S_COMMAND);
        launch_commands(parsed_params, -1, fds);
        wait_for_children(parsed_params); //aspetta i figli non gia aspettati (quindi le pipe)
    }
    else
    {
        waitpid_p(pid, &g_status, 0); //aspetta la command stream
        g_status = WEXITSTATUS(g_status);
    }
    dup2(original_stdin, STDIN_FILENO);
    reset_fd(&original_stdin);
}

static t_tree *skip_till_semicolon(t_tree *node)
{
    if (!node)
        return (NULL);
    if (node->type == SEMICOLON)
        return (node->right);
    return (skip_till_semicolon(node->right));
}

static void launch_commands(t_tree *node, int8_t prev_type, int fds[3])
{
    pid_t               pid;

    if (!node)
        exit(g_status);
    if (node->type != CMD)
    {
        if (node->type == PIPELINE)
            pipe_p(fds);
        pid = fork_p();
        if (pid == 0) //ogni volta che vado a sinistra forko (tanto o c'e' un comando o una subshell)
        {
            if (node->type == PIPELINE)
            {
                dup2_p(fds[1], STDOUT_FILENO);
                reset_fd(&fds[0]);
                reset_fd(&fds[1]);
            }
            launch_commands(node->left, prev_type, fds);
        }
        else
            parent(pid, fds, node->type == PIPELINE);
        if ((node->type == AND && g_status != 0) || (node->type == OR && g_status == 0))
            launch_commands(skip_till_semicolon(node), -1, fds);
        launch_commands(node->right, node->type, fds);
    }
    child(node, fds, prev_type);
}

// no: 0
// ch1: 0

static void child(t_tree *elem, int fds[3], int8_t prev_type)
{
    if (prev_type == PIPELINE)
        dup2_p(fds[2], STDIN_FILENO);
    exec_redirs(elem->cmd->redirs);
    elem->cmd->cmd_str = replace_env_vars(elem->cmd->cmd_str);
    exec(ft_getenv("PATH"), elem->cmd->cmd_str);
}

static void parent(pid_t pid, int fds[3], bool is_in_pipeline)
{
    reset_fd(&fds[1]);
    fds[2] = fds[0];
    if (!is_in_pipeline)
    {
        waitpid_p(pid, &g_status, 0);
        g_status = WEXITSTATUS(g_status);
        reset_fd(&fds[0]); //se dopo non c'e' pipe chiude la pipeline
    }
}

static void exec_redirs(t_list *redirs)
{
    t_list  *node;
    t_redir *redir;

    if (!redirs)
        return ;
    node = redirs;
    while (node)
    {
        redir = (t_redir *)node->content;
        if (redir->filename[0] == '$')
            redir->filename = replace_env_vars(redir->filename);
        if (redir->type == REDIR_INPUT)
            redir->fds[0] = open_p(redir->filename, O_RDONLY, 0644);
        else if (redir->type == REDIR_HEREDOC)
            redir->fds[0] = open_p(get_heredoc_filename(redir->heredoc_fileno), O_RDONLY, 0644);
        else if (redir->type == REDIR_OUTPUT)
            redir->fds[1] = open_p(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (redir->type == REDIR_APPEND)
            redir->fds[1] = open_p(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (redir->fds[0] != -42)
            dup2_p(redir->fds[0], STDIN_FILENO);
        if (redir->fds[1] != -42)
            dup2_p(redir->fds[1], STDOUT_FILENO);
        reset_fd(&redir->fds[1]);
        reset_fd(&redir->fds[0]);
        node = node->next;
    }
}

static void wait_for_children(t_tree *parsed_params) //aspetta tutti i figli (apparte quelli che erano gia stati aspettati, ovvero ; | || e &&)
{
    uint32_t    n_pipelines;

    n_pipelines = count_x(parsed_params, 0, PIPELINE);
    while (n_pipelines--)
    {
        waitpid_p(0, &g_status, 0);
        g_status = WEXITSTATUS(g_status);
    }
}

static uint32_t count_x(t_tree *node, uint32_t n, int8_t type)
{
    if (!node)
        return (n);
    if (node->type == type)
        n++;
    n += count_x(node->left, 0, type);
    n += count_x(node->right, 0, type);
    return (n);
}
