/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/02 17:17:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void    executor(t_tree *parsed_params)
{
    int             fds[3];
    int             original_stdin;
    static int      heredoc_fileno1 = 1;

    original_stdin = dup_p(STDIN_FILENO);
    create_heredocs(parsed_params, heredoc_fileno1);
    if (g_status != 130)
    {
        set_sighandler(&newline_signal, SIG_IGN);
        fds[2] = -1;
        launch_commands(parsed_params);
        wait_for_children(parsed_params);
    }
    dup2(original_stdin, STDIN_FILENO);
    reset_fd(&original_stdin);
}

static int parent(int fds[], int *heredoc_fileno)
{
    reset_fd(&fds[1]);
    reset_fd(&fds[2]);
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

    if (fds[2] != -1)
        dup2_p(fds[2], STDIN_FILENO);
    reset_fd(&fds[2]);
    heredoc_fileno2 = 1;
    while (1)
    {
        pid = fork_p();
        if (pid == 0)
        {
            set_sighandler(&display_and_quit_signal, &hide_and_abort_signal);
            replace_env_vars(&new_cmd_str);
            if (is_last_subcmd)
            {
                reset_fd(&fds[0]);
                if (!is_last)
                    dup2_p(fds[1], STDOUT_FILENO);
                reset_fd(&fds[1]);
            }
            exec_redirs(new_redirs, heredoc_fileno, heredoc_fileno2);
            exec(ft_getenv("PATH"), new_cmd_str);
        }
        else
        {
		    set_sighandler(SIG_IGN, SIG_IGN);
            heredoc_fileno2++;
            //TODO aggiornare la env var con ft_stenv leggendo da un file
            waitpid_p(pid, &g_status, 0);
            g_status = WEXITSTATUS(g_status);
            free(new_cmd_str);
            if ((separator == PH_AND && g_status != 0) || (separator == PH_OR && g_status == 0))
                break ;
            dup2_p(original_stdin, STDIN_FILENO);
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
            redir->fds[0] = open_p(redir->filename, O_RDONLY, 0644);
        else if (redir->type == REDIR_HEREDOC)
            redir->fds[0] = get_matching_heredoc(heredoc_fileno, heredoc_fileno2);
        else if (redir->type == REDIR_OUTPUT)
            redir->fds[1] = open_p(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (redir->type == REDIR_APPEND)
            redir->fds[1] = open_p(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (redir->fds[0] != -42)
        {
            dup2_p(redir->fds[0], STDIN_FILENO);
            reset_fd(&redir->fds[0]);
        }
        if (redir->fds[1] != -42)
        {
            dup2_p(redir->fds[1], STDOUT_FILENO);
            reset_fd(&redir->fds[1]);
        }
        node = node->next;
    }
}

static void wait_for_children(t_tree *parsed_params)
{
    uint32_t    n_cmds;

    n_cmds = count_cmds(parsed_params, 0);
    while (n_cmds--)
    {
        waitpid_p(0, &g_status, 0);
        g_status = WEXITSTATUS(g_status);
    }
}

static uint32_t count_cmds(t_tree *node, int n_cmds)
{
    uint32_t    n_cmds;
    t_list      *branches_list;

    if (!node)
        return (n_cmds);
    if (node->type == CMD)
        n_cmds += 1;
    branches_list = node->branches.branches_list;
    n_cmds += count_cmds(branches_list->prev, 0);
    n_cmds += count_cmds(branches_list->next, 0);
    return (n_cmds);
}
