/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/01 14:59:47 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static int parent(int fds[], int *heredoc_fileno);
static void child(t_parser *content, int fds[], bool is_last, int original_stdin, int heredoc_fileno);
static void exec_redirs(t_list *redirs, int heredoc_fileno, int heredoc_fileno2);
static void wait_for_children(t_list *parsed_params);

void executor(t_list *parsed_params)
{
    t_parser        *content;
    t_list          *node;
    int             fds[3];
    int             original_stdin;
    static int      heredoc_fileno = 1;

    original_stdin = dup(STDIN_FILENO);
    if (original_stdin == -1)
        ft_quit(24, NULL);
    //fare fork dove si chiama create_heredocs
    create_heredocs(parsed_params);
    fds[2] = -1;
    node = parsed_params;
    while (node)
    {
        content = (t_parser *)node->content;
        if (pipe(fds) == -1)
            ft_quit(18, NULL);
        content->pid = fork();
        if (content->pid == -1)
            ft_quit(19, NULL);
        if (content->pid == 0)
            child(content, fds, node->next == NULL, original_stdin, heredoc_fileno);
        else
            fds[2] = parent(fds, &heredoc_fileno);
        node = node->next;
    }
    wait_for_children(parsed_params);
    if (dup2(original_stdin, STDIN_FILENO) == -1 || reset_fd(&original_stdin) == -1)
        ft_quit(24, NULL);
}

static int parent(int fds[], int *heredoc_fileno)
{    
    if (reset_fd(&fds[1]) == -1 || (fds[2] != -1 && reset_fd(&fds[2]) == -1))
        ft_quit(29, NULL);
    return ((*heredoc_fileno)++, fds[0]);
}

static void child(t_parser *content, int fds[], bool is_last, int original_stdin, int heredoc_fileno)
{
    char            *new_cmd_str;
    t_list          *new_redirs;
    static char     ph_redir_stop = PH_REDIR_STOP;
    int             heredoc_fileno2;
    pid_t           pid;
    bool            is_last_subcmd;
    char            separator;

    if (fds[2] != -1 && (dup2(fds[2], STDIN_FILENO) == -1 || reset_fd(&fds[2]) == -1))
        ft_quit(25, NULL);
    heredoc_fileno2 = 1;
    while (1)
    {
        new_cmd_str = ft_strdup_until(content->cmd_str, "\323\321\320", &separator); //fino a '\0' o PH_SEMICOLON o PH_OR o PH_AND
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
            if (is_last_subcmd)
                if (reset_fd(&fds[0]) == -1 || (!is_last && dup2(fds[1], STDOUT_FILENO) == -1) || reset_fd(&fds[1]) == -1)
                    ft_quit(27, NULL);
            exec_redirs(new_redirs, heredoc_fileno, heredoc_fileno2);
            exec(ft_getenv("PATH"), new_cmd_str);
        }
        else
        {
            heredoc_fileno2++;
            //TODO aggiornare la env var con ft_stenv leggendo da un file
            waitpid(pid, &g_status, 0);
            g_status = WEXITSTATUS(g_status);
            free(new_cmd_str);
            if ((separator == PH_AND && g_status != 0) || (separator == PH_OR && g_status == 0))
                break ;
            if (dup2(original_stdin, STDIN_FILENO) == -1)
                ft_quit(24, NULL);
        }
    }
    exit(g_status);
}

static void exec_redirs(t_list *redirs, int heredoc_fileno, int heredoc_fileno2)
{
    t_list          *node;
    t_redir         *redir;

    if (!redirs)
        return ;
    node = redirs;
    while (node)
    {
        redir = (t_redir *)node->content;
        if (redir->filename[0] == '$')
            replace_env_vars(&redir->filename);
        if (redir->type == REDIR_INPUT)
            redir->fds[0] = open(redir->filename, O_RDONLY, 0644);
        else if (redir->type == REDIR_HEREDOC)
            redir->fds[0] = get_matching_heredoc(heredoc_fileno, heredoc_fileno2);
        else if (redir->type == REDIR_OUTPUT)
            redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (redir->type == REDIR_APPEND)
            redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (redir->fds[1] == -1 || redir->fds[0] == -1)
            ft_quit(22, NULL);
        if (redir->fds[0] != -42 && ((dup2(redir->fds[0], STDIN_FILENO) == -1 || (redir->fds[0] != STDIN_FILENO && reset_fd(&redir->fds[0]) == -1))))
            ft_quit(26, NULL);
        if (redir->fds[1] != -42 && ((dup2(redir->fds[1], STDOUT_FILENO) == -1 || (redir->fds[1] != STDOUT_FILENO && reset_fd(&redir->fds[1]) == -1))))
            ft_quit(24, NULL);
        node = node->next;
    }
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
