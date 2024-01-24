/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/24 15:49:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static int parent(int fds[], char *heredo_filename, t_data *data);
static void child(t_parser *content, int fds[], int prev_out_fd, char *heredoc_filename, bool is_last, int original_stdin, t_data *data);
static void exec_redirs(t_list *redirs, int heredoc_fd, int original_stdin, t_data *data);
static void wait_for_children(unsigned int n_cmds);

void executor(t_list *parsed_params, t_data *data)
{
    t_parser        *content;
    t_list          *node;
    int             fds[2];
    int             prev_out_fd;
    char            *heredoc_filename;
    int             original_stdin;

    original_stdin = dup(STDIN_FILENO);
    if (original_stdin == -1)
        ft_quit(24, NULL, data);
    prev_out_fd = -1;
    node = parsed_params;
    while (node)
    {
        heredoc_filename = NULL;
        content = (t_parser *)node->content;
        if (pipe(fds) == -1)
            ft_quit(18, NULL, data);
        if (is_heredoc(content->redirs)) 
            heredoc_filename = get_filename(data);
        content->pid = fork();
        if (content->pid == -1)
            ft_quit(19, NULL, data);
        if (content->pid != 0)
            prev_out_fd = parent(fds, heredoc_filename, data);
        else if (content->pid == 0)
            child(content, fds, prev_out_fd, heredoc_filename, node->next == NULL, original_stdin, data);
        node = node->next;
    }
    resume(parsed_params);
    wait_for_children(ft_lstsize(parsed_params));
    if (dup2(original_stdin, STDIN_FILENO) == -1 || close(original_stdin) == -1)
        ft_quit(24, NULL, data);
}

static int parent(int fds[], char *heredo_filename, t_data *data)
{
    free(heredo_filename);
    if (close(fds[1]) == -1)
        ft_quit(29, NULL, data);
    return (fds[0]);
}

static void child(t_parser *content, int fds[], int prev_out_fd, char *heredoc_filename, bool is_last, int original_stdin, t_data *data)
{
    int     heredoc_fd;

    heredoc_fd = -1;
    if (prev_out_fd != -1)
    {
        if (dup2(prev_out_fd, STDIN_FILENO) == -1 || close(prev_out_fd) == -1)
            ft_quit(25, NULL, data);
    }
    if (is_heredoc(content->redirs) == true)
        heredoc_fd = open(heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    exec_redirs(content->redirs, heredoc_fd, original_stdin, data);
    if (is_heredoc(content->redirs) == true)
    {
        if (heredoc_fd == -1 || dup2(heredoc_fd, STDIN_FILENO) == -1 || close(heredoc_fd) == -1)
        {
            free(heredoc_filename);
            ft_quit(26, NULL, data);
        }
    }
    free(heredoc_filename);
    if (close(fds[0]) == -1 || (!is_last && dup2(fds[1], STDOUT_FILENO) == -1) || close(fds[1]) == -1)
        ft_quit(27, NULL, data);
    exec(getenv("PATH"), content->cmd_str, data);
}

static void exec_redirs(t_list *redirs, int heredoc_fd, int original_stdin, t_data *data)
{
    t_list          *node;
    t_redir         *redir;
    int8_t          append_or_trunc;

    node = redirs;
    while (node)
    {
        redir = (t_redir *)node->content;
        if (redir->fds[0] == -42)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                if (dup2(original_stdin, STDIN_FILENO) == -1)
                    ft_quit(28, NULL, data);
                fill_heredoc(redir->filename, heredoc_fd);
            }
            else if (redir->type == REDIR_INPUT)
            {
                redir->fds[0] = open(redir->filename, O_RDONLY, 0644);
                if (redir->fds[0] == -1 || dup2(redir->fds[0], STDIN_FILENO) == -1 || close(redir->fds[0]) == -1)
                    ft_quit(21, NULL, data);
            }
        }
        else if (redir->fds[1] == -42)
        {
            append_or_trunc = O_TRUNC * (redir->type == REDIR_OUTPUT) + O_APPEND * (redir->type == REDIR_APPEND);
            if (redir->type == REDIR_OUTPUT || redir->type == REDIR_HEREDOC)
            {
                redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | append_or_trunc, 0644);
                if (redir->fds[1] == -1)
                    ft_quit(22, NULL, data);
            }
            if (dup2(redir->fds[1], STDOUT_FILENO) == -1 || close(redir->fds[1]) == -1)
                ft_quit(23, NULL, data);
        }
        node = node->next;
    }
}

static void wait_for_children(unsigned int n_cmds)
{
    unsigned int i;

    i = 0;
    while (i < n_cmds)
    {
        wait(NULL);
        i++;
    }
}
