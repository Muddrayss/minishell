/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/20 18:54:10 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_command(t_parser *content, int fds[], t_data *data, int8_t flag);
static void heredoc(char *limiter, int fd);

void executor(t_list *parsed_params, t_data *data)
{
    t_parser        *content;
    t_list          *node;
    int             fds[2];
    int prev_output_fd;
    pid_t           pid;
    unsigned int    n_cmds;

    node = parsed_params;
    n_cmds = ft_lstsize(node);
    if (n_cmds == 1)
    {
        content = (t_parser *)node->content;
        exec_single_cmd(getenv("PATH"), content->cmd_str, data->envp, content->redirs, data);
    }
    else
    {
        node = parsed_params;
        prev_output_fd = STDIN_FILENO;
        while (node)
        {
            content = (t_parser *)node->content;
            if (pipe(fds) == -1)
                ft_quit(18, NULL, data);
            fds[0] = prev_output_fd;
            pid = fork();
            if (pid == -1)
                ft_quit(19, NULL, data);
            if (pid == 0)
            {
                handle_command(content, fds, data, IS_LAST);
            }
            else
            {
                if (close(fds[0]) == -1)
                    ft_quit(20, NULL, data);
                prev_output_fd = fds[1];
            }
            node = node->next;
        }
       // wait_all_commands(n_cmds, data);
    }
    
}

static void handle_command(t_parser *content, int fds[], t_data *data, int8_t flag)
{   
    exec_redirs(content->redirs, data);
    if ((dup2(fds[0], STDIN_FILENO) == -1)
        || (flag != IS_LAST && dup2(fds[1], STDOUT_FILENO) == -1)
        || close(fds[0]) == -1
        || close(fds[1]) == -1)
        ft_quit(20, NULL, data);
    exec(getenv("PATH"), content->cmd_str, data->envp, data);
}

void exec_redirs(t_list *redirs, t_data *data)
{
    t_list          *node;
    t_redir         *redir;
    unsigned int    i;

    node = redirs;
    i = 2;
    while (node)
    {
        redir = (t_redir *)redirs->content;
        if (redir->fds[0] == -42)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                heredoc(redir->filename, i);
                i++;
            }
            else if (redir->type == REDIR_INPUT)
            {
                redir->fds[0] = open(redir->filename, O_RDONLY, 0644);
                if (redir->fds[0] == -1)
                    ft_quit(21, NULL, data);
            }
            dup2(redir->fds[0], STDIN_FILENO);
            close(redir->fds[0]);
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
            dup2(redir->fds[1], STDOUT_FILENO);
            close(redir->fds[1]);
        }
        node = node->next;
    }
}

static void heredoc(char *limiter, int fd)
{
    char *str;
    
    (void)limiter;
    str = NULL;
    while (1)
    {
        str = readline("> ");
        if (!str)
            break ;
        if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
            break ;
        ft_putstr_fd(str, fd);
        free(str);
    }
    free(str);
}

//TODO gestire pie' here doc di seguito anche tra pipe e pipe. basta aprire con open (O_APPEND) il primo e poi fare putstr del secondo sul primo. chiudendo il secondo.
