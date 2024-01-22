/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/22 17:14:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void child(t_parser *content, int fds[], bool is_last, t_data *data);
static void heredoc(char *limiter);
// static void resume(t_list *node);
static void wait_for_children(unsigned int n_cmds);
static void parent(t_list *redirs, int fds[], t_data *data);

void executor(t_list *parsed_params, t_data *data)
{
    t_parser        *content;
    t_list          *node;
    int             fds[2];

    node = parsed_params;
    while (node)
    {
        content = (t_parser *)node->content;
        if (pipe(fds) == -1)
            ft_quit(18, NULL, data);
        content->pid = fork();
        if (content->pid == -1)
            ft_quit(19, NULL, data);
        if (content->pid == 0)
            child(content, fds, true * (node->next == NULL), data);
        else
            parent(content->redirs, fds, data);
        node = node->next;
    }
    // resume(parsed_params);
    wait_for_children(ft_lstsize(parsed_params));
}

static void parent(t_list *redirs, int fds[], t_data *data)
{
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    exec_redirs(redirs, data); //heredoc scrive nell'input della pipe
    close(fds[0]);
}

static void child(t_parser *content, int fds[], bool is_last, t_data *data)
{   
    close(fds[0]);
    if (!is_last)
        dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    //kill(getpid(), SIGSTOP);
    exec(getenv("PATH"), content->cmd_str, data);
}

// static void resume(t_list *node)
// {
//     t_parser *content;

//     while (node)
//     {
//         content = (t_parser *)node->content;
//         kill(content->pid, SIGCONT);
//         node = node->next;
//     }
// }

static void wait_for_children(unsigned int n_cmds)
{
    unsigned int i;

    i = 0;
    while (i++ < n_cmds)
        wait(NULL);
}

void exec_redirs(t_list *redirs, t_data *data)
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
                heredoc(redir->filename);
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

static void heredoc(char *limiter)
{
    char    *str;
    size_t  str_len;
    size_t  limiter_len;
  
    g_signals.in_cmd = 1;
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
        ft_putstr_fd(str, 1);
        ft_putchar_fd('\n', 1);
        free(str);
        str = NULL; //per evitare la double free
    }
    free(str);
    g_signals.in_cmd = 0;
}

