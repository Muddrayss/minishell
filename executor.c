/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/06 17:31:45 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void     launch_commands(t_tree *node, int8_t prev_separator_type, int8_t next_separator_type);
static void     child(t_tree *elem, int fds[2], int8_t prev, int8_t next);
static void     parent(pid_t pid, int fds[3], bool is_after_pipeline);
static void     dup_and_close(int *to_dup_old, int to_dup_new, int *to_close);
static void     exec_cmd(t_tree *elem, int8_t prev, int8_t next);
static void     exec_redirs(t_list *redirs, int heredoc_fileno);
static void     wait_for_children(t_tree *parsed_params);
static uint32_t count_cmds(t_tree *node, int n_cmds);

//E" NORMALE CHE CRASHI NELL'EXECUTOR!!!! ANCORA NON E' STATO AGGIUSTATO ALL'ALBERO
void    executor(t_tree *parsed_params)
{
    int             original_stdin;

    original_stdin = dup_p(STDIN_FILENO);
    create_heredocs(parsed_params);
    if (g_status != 130)
    {
        set_sighandler(&newline_signal, SIG_IGN);
        launch_commands(parsed_params, 0, 0);
        wait_for_children(parsed_params);
    }
    dup2(original_stdin, STDIN_FILENO);
    reset_fd(&original_stdin);
}

//inorder traversal search (L, N, R)
static void launch_commands(t_tree *node, int8_t prev_separator_type, int8_t next_separator_type)
{
    if (!node)
        return ;
    launch_commands(node->left, next_separator_type, node->type);
    if (node->type == CMD)
        exec_cmd(node, prev_separator_type, next_separator_type); //fa pipe, fa fork, esegue, ed aspetta settando g_status. se il parent leaf è un pipe, duplica l'input o l'output, altrimenti ignora 
    if ((node->type == AND && g_status == 0) || (node->type == OR && g_status != 0))
        return ; //breaka e non esegue i comandi successivo
    launch_commands(node->right, prev_separator_type, node->type);
}

static void exec_cmd(t_tree *elem, int8_t prev, int8_t next)
{
    pid_t       pid;
    static int  fds[3];

    if (next == PIPELINE)
        pipe_p(fds);
    pid = fork_p();
    if (pid == 0)
        child(elem, fds, prev, next);
    else
        parent(pid, fds, prev == PIPELINE);
}

static void child(t_tree *elem, int fds[2], int8_t prev, int8_t next)
{
    static int  heredoc_fileno = 0;
    t_list      *redirs;
    char        *cmd_str;

    redirs = elem->cmd->redirs;
    cmd_str = elem->cmd->cmd_str;
    if (next == PIPELINE)
        dup_and_close(&fds[1], STDOUT_FILENO, &fds[0]);
    if (prev == PIPELINE)
        dup_and_close(&fds[2], STDIN_FILENO, &fds[1]);
    reset_fd(&fds[0]);
    exec_redirs(redirs, heredoc_fileno++);
    exec(get_data()->cmd_path, cmd_str);
}

static void parent(pid_t pid, int fds[3], bool is_after_pipeline)
{
    reset_fd(&fds[1]);
    fds[2] = fds[0];
    if (!is_after_pipeline)
        waitpid(pid, &g_status, 0);
}

static void dup_and_close(int *to_dup_old, int to_dup_new, int *to_close)
{
    reset_fd(to_close);
    dup2_p(*to_dup_old, to_dup_new);
    reset_fd(to_dup_old);
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

static void wait_for_children(t_tree *parsed_params)
{
    uint32_t    n_cmds;

    n_cmds = count_cmds(parsed_params, 0);
    while (n_cmds--)
    {
        waitpid_p(0, &g_status, 0);
        g_status = WEXITSTATUS(g_status);
    }
}

static uint32_t count_cmds(t_tree *node, int n_cmds)
{
    if (!node)
        return (n_cmds);
    if (node->type == CMD)
        n_cmds++;
    n_cmds += count_cmds(node->left, 0);
    n_cmds += count_cmds(node->right, 0);
    return (n_cmds);
}
