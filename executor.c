/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/21 18:47:02 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_command(t_parser *content, int fds[], t_data *data, int8_t flag);
static void heredoc(char *limiter, int fd);
static void resume(t_list *node);

void executor(t_list *parsed_params, t_data *data)
{
    t_parser        *content;
    t_list          *node;
    int             fds[2];
    int             prev_output_fd;
    unsigned int    n_cmds;
    int             status;

    node = parsed_params;
    status = 0;
    n_cmds = ft_lstsize(node);
    if (n_cmds == 1)
    {
        content = (t_parser *)node->content;
        exec_single_cmd(getenv("PATH"), content->cmd_str, data->envp, content->redirs, data);
    }
    else
    {
        node = parsed_params;
        prev_output_fd = STDOUT_FILENO;
        while (node)
        {
            content = (t_parser *)node->content;
            if (pipe(fds) == -1)
                ft_quit(18, NULL, data);
            fds[0] = prev_output_fd;
            content->pid = fork();
            if (content->pid == -1)
                ft_quit(19, NULL, data);
            if (content->pid == 0)
            {
                handle_command(content, fds, data, IS_LAST);
            }
            else
            {
                while (!WIFSTOPPED(status) && !WIFEXITED(status) && !WIFSIGNALED(status))
                {
                    waitpid(content->pid, &status, WUNTRACED);
                }
                if (close(fds[0]) == -1)
                    ft_quit(20, NULL, data);
                prev_output_fd = fds[1];
            }
            node = node->next;
        }
        resume(parsed_params);
        // wait_all_commands(n_cmds, data);
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

static void handle_command(t_parser *content, int fds[], t_data *data, int8_t flag)
{    
    exec_redirs(content->redirs, fds[0], data);
    kill(getpid(), SIGSTOP);
    if ((dup2(fds[0], STDIN_FILENO) == -1) || (flag != IS_LAST && dup2(fds[1], STDOUT_FILENO) == -1) || close(fds[0]) == -1 || close(fds[1]) == -1)
        ft_quit(20, NULL, data);
    exec(getenv("PATH"), content->cmd_str, data->envp, data);
}

void exec_redirs(t_list *redirs, int in_fd, t_data *data)
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
                heredoc(redir->filename, in_fd);
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

static size_t   get_max_num(size_t num1, size_t num2)
{
    if (num1 > num2)
        return (num1);
    return (num2);
}

static void heredoc(char *limiter, int fd)
{
    char    *str;
    size_t  str_len;
    size_t  limiter_len;
  
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
        free(str);
    }
    free(str);
}

