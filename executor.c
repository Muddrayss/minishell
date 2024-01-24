/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/24 14:44:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static int  parent(t_list *redirs, pid_t child_pid, int original_stdin, int fds[], char *heredoc_filename, t_data *data);
static void child(t_parser *content, int fds[], int prev_out_fd, char *heredoc_filename, bool is_last, t_data *data);
static void exec_redirs(t_list *redirs, int heredoc_fd, int original_stdin, t_data *data);
static void resume(t_list *node);
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
            prev_out_fd = parent(content->redirs, content->pid, original_stdin, fds, heredoc_filename, data);
        else if (content->pid == 0)
            child(content, fds, prev_out_fd, heredoc_filename, node->next == NULL, data);
        node = node->next;
    }
    resume(parsed_params);
    wait_for_children(ft_lstsize(parsed_params));
    dup2(original_stdin, STDIN_FILENO);
}

static int parent(t_list *redirs, pid_t child_pid, int original_stdin, int fds[], char *heredoc_filename, t_data *data)
{
    int heredoc_fd;

    kill(child_pid, SIGSTOP);
    if (heredoc_filename)
        heredoc_fd = open(heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    free(heredoc_filename);
    close(fds[1]);
    exec_redirs(redirs, heredoc_fd, original_stdin, data);
    close(heredoc_fd);
    return (fds[0]);
}

static void child(t_parser *content, int fds[], int prev_out_fd, char *heredoc_filename, bool is_last, t_data *data)
{
    int     heredoc_fd;

    if (prev_out_fd != -1)
    {
        dup2(prev_out_fd, STDIN_FILENO);
        close(prev_out_fd);
    }
    if (is_heredoc(content->redirs) == true)
    {
        heredoc_fd = open(heredoc_filename, O_RDONLY, 0644);
        dup2(heredoc_fd, STDIN_FILENO);
        close(heredoc_fd);
    }
    free(heredoc_filename);
    close(fds[0]);
    if (!is_last)
        dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    exec(getenv("PATH"), content->cmd_str, data);
}

static void exec_redirs(t_list *redirs, int heredoc_fd, int original_stdin, t_data *data)
{
    t_list          *node;
    t_redir         *redir;

    node = redirs;
    while (node)
    {
        redir = (t_redir *)node->content;
        if (redir->fds[0] == -42)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                dup2(original_stdin, STDIN_FILENO);
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
            if (redir->type == REDIR_OUTPUT)
            {
                redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (redir->fds[1] == -1)
                    ft_quit(22, NULL, data);
            }
            else if (redir->type == REDIR_APPEND)
            {
                redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (redir->fds[1] == -1)
                    ft_quit(22, NULL, data);
            }
            if (dup2(redir->fds[1], STDOUT_FILENO) == -1 || close(redir->fds[1]))
                ft_quit(23, NULL, data);
        }
        node = node->next;
    }
}

static void resume(t_list *node)
{
    t_parser *content;

    while (node)
    {
        content = (t_parser *)node->content;
        kill(content->pid, SIGCONT);
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
