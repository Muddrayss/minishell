/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/29 21:05:16 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static int parent(int fds[]);
static void child(t_parser *content, int fds[], bool is_last, int original_stdin, int heredoc_fileno);
static void exec_redirs(t_list *redirs);
static void wait_for_children(t_list *parsed_params);

void executor(t_list *parsed_params)
{
    t_parser        *content;
    t_list          *node;
    int             fds[3];
    int             prev_out_fd;
    int             original_stdin;
    static int      heredoc_fileno = 1;

    original_stdin = dup(STDIN_FILENO);
    if (original_stdin == -1)
        ft_quit(24, NULL);
    create_heredocs(parsed_params);
    prev_out_fd = -1;
    node = parsed_params;
    while (node)
    {
        content = (t_parser *)node->content;
        if (pipe(fds) == -1)
            ft_quit(18, NULL);
        fds[2] = prev_out_fd;
        content->pid = fork();
        if (content->pid == -1)
            ft_quit(19, NULL);
        if (content->pid == 0)
            child(content, fds, node->next == NULL, original_stdin, heredoc_fileno);
        else
            prev_out_fd = parent(fds);
        node = node->next;
        heredoc_fileno++;
    }
    wait_for_children(parsed_params);
    if (dup2(original_stdin, STDIN_FILENO) == -1 || close(original_stdin) == -1)
        ft_quit(24, NULL);
}

static int parent(int fds[])
{    
    init_in_cmd_signals();
    if (close(fds[1]) == -1 || (fds[2] != -1 && close(fds[2]) == -1))
        ft_quit(29, NULL);
    return (fds[0]);
}

static void child(t_parser *content, int fds[], bool is_last, int original_stdin, int heredoc_fileno)
{
    char            *new_cmd_str;
    t_list          *new_redirs;
    static char     ph_redir_stop = PH_REDIR_STOP;
    int             heredoc_fileno2;
    pid_t           pid;
    bool            is_last_subcmd;

    if (fds[2] != -1 && (dup2(fds[2], STDIN_FILENO) == -1 || close(fds[2]) == -1))
        ft_quit(25, NULL);
    heredoc_fileno2 = 1;
    while (1)
    {
        new_cmd_str = ft_strdup_until(content->cmd_str, PH_SEMICOLON); //fino a '\0' o PH_SEMICOLON
        new_redirs = ft_lstdup_until(content->redirs, &ph_redir_stop);  //fino a NULL o PH_REDIR_STOP
        if ((!new_cmd_str || new_cmd_str[0] == '\0') && !new_redirs) //se c'e' una redir la stringa e' vuota ma devi comunque eseguire
            break ;
        is_last_subcmd = check_last_subcmd(content->cmd_str);
        pid = fork();
        if (pid == -1)
            ft_quit(26, NULL);
        if (pid == 0)
        {
            replace_env_vars(&new_cmd_str);
            if (new_redirs)
                exec_redirs(new_redirs);
            if (is_heredoc(new_redirs))
            {
                if (dup2(get_matching_heredoc(heredoc_fileno, heredoc_fileno2), STDIN_FILENO) == -1)
                    ft_quit(32, NULL);
            }    
            if (is_last_subcmd)
            {
                if (close(fds[0]) == -1 || (!is_last && dup2(fds[1], STDOUT_FILENO) == -1) || close(fds[1]) == -1)
                    ft_quit(27, NULL);
            }
            exec(ft_getenv("PATH"), new_cmd_str);
        }
        else
        {
            if (is_heredoc(new_redirs))
                heredoc_fileno2++;
            //TODO aggiornare la env var con ft_stenv leggendo da un file
            waitpid(pid, &g_status, 0);
            g_status = WEXITSTATUS(g_status);
            free(new_cmd_str);
            if (dup2(original_stdin, STDIN_FILENO) == -1)
                ft_quit(24, NULL);
        }
    }
    exit(g_status);
}

static void exec_redirs(t_list *redirs)
{
    t_list          *node;
    t_redir         *redir;

    node = redirs;
    while (node)
    {
        redir = (t_redir *)node->content;
        if (redir->filename[0] == '$')
            replace_env_vars(&redir->filename);
        if (redir->fds[0] == -42)
        {
            if (redir->type == REDIR_INPUT)
            {
                redir->fds[0] = open(redir->filename, O_RDONLY, 0644);
                if (redir->fds[0] == -1)
                    ft_quit(21, NULL);
            }
        }
        else if (redir->fds[1] == -42)
        {
            if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
            {
                if ((redir->type == REDIR_OUTPUT))
                    redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                else if (redir->type == REDIR_APPEND)
                    redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (redir->fds[1] == -1)
                    ft_quit(22, NULL);
            }
        }
        node = node->next;
    }
    if (redir->fds[0] != -42 && (dup2(redir->fds[0], STDIN_FILENO) == -1 || (redir->fds[0] != STDIN_FILENO && close(redir->fds[0]) == -1)))
        ft_quit(26, NULL);
    if (dup2(redir->fds[1], STDOUT_FILENO) == -1 || (redir->fds[1] != STDOUT_FILENO && close(redir->fds[1]) == -1))
        ft_quit(24, NULL);
}

static void wait_for_children(t_list *parsed_params)
{
    t_parser        *content;
    t_list          *node;

    node = parsed_params;
    while (node)
    {
        content = (t_parser *)node->content;
        if (waitpid(content->pid, &g_status, 0) == -1)
            ft_quit(98, NULL); //forse e' meglio waitpid(0, , )
        g_status = WEXITSTATUS(g_status);
        node = node->next;
    }
}
