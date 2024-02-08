/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/08 16:41:47 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void     launch_commands(t_tree *node, int8_t prev_type, int8_t next_type, int fds[3]);
static void     child(t_tree *elem, int fds[3], int8_t prev, int8_t next);
static void     parent(pid_t pid, int fds[3], bool is_in_pipeline);
static void     exec_redirs(t_list *redirs, int heredoc_fileno);
static void     wait_for_children(t_tree *parsed_params);
static uint32_t count_x(t_tree *node, int n, int8_t type);

void    executor(t_tree *parsed_params)
{
    int original_stdin;
    int fds[3] = {-1, -1, -1};

    original_stdin = dup_p(STDIN_FILENO);
    create_heredocs(parsed_params);
    if (g_status != 130)
    {
        launch_commands(parsed_params, -1, -1, fds);
        wait_for_children(parsed_params);
    }
    dup2(original_stdin, STDIN_FILENO);
    reset_fd(&original_stdin);
}

static void launch_commands(t_tree *node, int8_t prev_type, int8_t next_type, int fds[3])
{
    pid_t       pid;
    //gli fd statici non funzioanno con piu pipe di fila (la seconda pipe sovrascrive quelli della prima), passarli come argomenti??
    if (!node)
        return ; //forse meglio exit essendo in un subprocess
    if (node->type != CMD)
    {
        if (node->type == PIPELINE)
            pipe_p(fds);
        pid = fork_p();
        if (pid == 0) //ogni volta che vado a sinistra forko (tanto o c'e' un comando o una subshell)
            launch_commands(node->left, prev_type, node->type, fds);
        else
            parent(pid, fds, node->type == PIPELINE);
        if ((node->type == AND && g_status != EXIT_SUCCESS) || (node->type == OR && g_status == EXIT_SUCCESS))
            return ;
        launch_commands(node->right, node->type, -1, fds);
        return ;
    }
    if (next_type == -1)
    {
        pid = fork_p();
        if (pid > 0)
        {
            parent(pid, fds, false);
            return ;
        }
    }
    child(node, fds, prev_type, next_type);
}

static void child(t_tree *elem, int fds[3], int8_t prev, int8_t next)
{
    static int  heredoc_fileno = 0;
    t_list      *redirs;
    char        *cmd_str;

    redirs = elem->cmd->redirs;
    cmd_str = elem->cmd->cmd_str;
    if (next == PIPELINE)
        dup2_p(fds[1], STDOUT_FILENO);
    if (prev == PIPELINE)
        dup2_p(fds[2], STDIN_FILENO);
    reset_fd(&fds[0]);
    reset_fd(&fds[1]);
    exec_redirs(redirs, heredoc_fileno++);
    cmd_str = replace_env_vars(cmd_str);
    exec(ft_getenv("PATH"), cmd_str);
}

static void parent(pid_t pid, int fds[3], bool is_in_pipeline)
{
    reset_fd(&fds[1]);
    fds[2] = fds[0];
    if (!is_in_pipeline)
    {
        waitpid_p(pid, &g_status, 0);
        g_status = WEXITSTATUS(g_status);
        printf("status: %d\n", g_status);
        reset_fd(&fds[0]); //se dopo non c'e' pipe chiude la pipeline
    }
}

static void exec_redirs(t_list *redirs, int heredoc_fileno)
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
            redir->fds[0] = open_p(get_heredoc_filename(heredoc_fileno), O_RDONLY, 0644);
        else if (redir->type == REDIR_OUTPUT)
            redir->fds[1] = open_p(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (redir->type == REDIR_APPEND)
            redir->fds[1] = open_p(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (redir->fds[0] != -42)
        {
            dup2_p(redir->fds[0], STDIN_FILENO);
            reset_fd(&redir->fds[0]);
        }
        if (redir->fds[1] != -42)
        {
            dup2_p(redir->fds[1], STDOUT_FILENO);
            reset_fd(&redir->fds[1]);
        }
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

static uint32_t count_x(t_tree *node, int n, int8_t type)
{
    if (!node)
        return (n);
    if (node->type == type)
        n++;
    n += count_x(node->left, 0, type);
    n += count_x(node->right, 0, type);
    return (n);
}
