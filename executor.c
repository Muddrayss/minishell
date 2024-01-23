/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/23 20:12:30 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void child(t_parser *content, int fds[], int prev_out_fd, char *heredoc_filename, bool is_last, t_data *data);
static void fill_heredoc(char *limiter, int fd);
static bool is_heredoc(t_list *redirs);
static void resume(t_list *node);
static void wait_for_children(unsigned int n_cmds);
static int  parent(t_list *redirs, pid_t child_pid, int original_stdin, int fds[], char *heredoc_filename, t_data *data);
static char *get_filename(t_data *data);

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
        content = (t_parser *)node->content;
        if (pipe(fds) == -1)
            ft_quit(18, NULL, data);
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

static bool is_heredoc(t_list *redirs)
{
    t_list  *node;
    t_redir *redir;

    node = redirs;
    while (node)
    {
        redir = (t_redir *)node->content;
        if (redir->type == REDIR_HEREDOC)
            return (true);
        node = node->next;
    }
    return (false);
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

static char *get_filename(t_data *data)
{
    static int  i = 0;
    char        *idx;
    char        *tmp;
    char        *filename;

    idx = ft_itoa(++i);
    tmp = ft_strjoin(data->starting_dir, "/tmp/.heredoc_");
    filename = ft_strjoin(tmp, idx);
    free(tmp);
    free(idx);
    if (!filename)
        ft_quit(20, NULL, data);
    return (filename);
}

bool exec_redirs(t_list *redirs, int heredoc_fd, int original_stdin, t_data *data)
{
    t_list          *node;
    t_redir         *redir;
    bool            is_heredoc;

    is_heredoc = false;
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
                is_heredoc = true;
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
    return (is_heredoc);
}

static size_t   get_max_num(size_t num1, size_t num2)
{
    if (num1 > num2)
        return (num1);
    return (num2);
}

static void fill_heredoc(char *limiter, int fd)
{
    char    *str;
    size_t  str_len;
    size_t  limiter_len;
  
    g_signals.in_heredoc = 1;
    str = NULL;
    limiter_len = ft_strlen(limiter);
    if (is_shell_space(limiter[limiter_len - 1]))
        limiter_len--;
    while (!g_signals.sigint)
    {
        str = readline("> ");
        if (!str)
            break ;
        str_len = ft_strlen(str);
        if (ft_strncmp(limiter, str, get_max_num(str_len, limiter_len)) == 0)
            break ;
        ft_putstr_fd(str, fd);
        ft_putchar_fd('\n', fd);
        free(str);
        str = NULL; //per evitare la double free
    }
    free(str);
    g_signals.in_heredoc = 0;
}

