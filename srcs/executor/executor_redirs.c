/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:39:47 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 21:25:10 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void exec_fd_redirs(t_redir *redir);
static void exec_file_redirs(t_redir *redir);
static int  open_redir_file(t_redir *redir);

void exec_redirs(t_list *redirs)
{
    t_redir *redir;

    while (redirs)
    {
        redir = (t_redir *)redirs->content;
        redir->filename = replace_env_vars(redir->filename);
        redir->filename = replace_wildcards(redir->filename);
        redir->filename = clear_quotes(redir->filename);
        exec_fd_redirs(redir);
        exec_file_redirs(redir);
        redirs = redirs->next;
    }
}

static void exec_fd_redirs(t_redir *redir)
{
    if (redir->fds[0] != -42)
        dup2_p(redir->fds[0], STDIN_FILENO);
    if (redir->fds[1] != -42)
        dup2_p(redir->fds[1], STDOUT_FILENO);
    reset_fd(&redir->fds[0]);
    reset_fd(&redir->fds[1]);
}

static void exec_file_redirs(t_redir *redir)
{
    int file_fd;
    int dup_target;

    file_fd = -42;
    file_fd = open_redir_file(redir);
    if (redir->type == REDIR_INPUT || redir->type == REDIR_INPUT_FD || redir->type == REDIR_HEREDOC)
        dup_target = STDIN_FILENO;
    else if (redir->type == REDIR_OUTPUT || redir->type == REDIR_OUTPUT_FD || redir->type == REDIR_APPEND_FD)
        dup_target = STDOUT_FILENO;
    dup2_p(file_fd, dup_target);
    reset_fd(&file_fd);
}

//TODO restituisce sempre 1
static int  open_redir_file(t_redir *redir)
{
    int     fd;
    char    *heredoc_filename;

    fd = -1;
    if (redir->type == REDIR_INPUT)
        fd = open_p(redir->filename, O_RDONLY, 0644);
    else if (redir->type == REDIR_HEREDOC)
    {
        heredoc_filename = get_heredoc_filename(redir->heredoc_fileno); 
        fd = open_p(heredoc_filename, O_RDONLY, 0644);
        free(heredoc_filename);
    }
    else if (redir->type == REDIR_OUTPUT)
        fd = open_p(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (redir->type == REDIR_APPEND)
        fd = open_p(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    return (fd);
}