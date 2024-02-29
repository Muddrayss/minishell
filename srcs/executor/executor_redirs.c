/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:39:47 by craimond          #+#    #+#             */
/*   Updated: 2024/02/29 17:38:42 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void exec_file_and_fd_redirs(t_redir *redir);
static int open_redir_file(t_redir *redir);

void exec_redirs(t_list *redirs)
{
    t_redir *redir;
    char    *tmp;

    while (redirs)
    {
        redir = (t_redir *)redirs->content;
        tmp = redir->filename;
        if (redir->filename)
        {
            redir->filename = replace_env_vars(redir->filename, false);
            free(tmp);
            tmp = redir->filename;
            redir->filename = replace_wildcards(redir->filename);
            free(tmp);
            redir->filename = clear_quotes(redir->filename);
        }
        exec_file_and_fd_redirs(redir);
        redirs = redirs->next;
    }
}

static void exec_file_and_fd_redirs(t_redir *redir)
{
    int file_fd;

    file_fd = open_redir_file(redir);
    if (file_fd == -1)
        return ;
    if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
        dup2_p(file_fd, STDIN_FILENO);
    else if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
        dup2_p(file_fd, STDOUT_FILENO);
    reset_fd(&file_fd);
}

static int  open_redir_file(t_redir *redir)
{
    int     fd;
    char    *heredoc_filename;

    if (!redir->filename)
        return (-1);
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
    else
        fd = open_p(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    return (fd);
}