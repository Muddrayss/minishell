/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 10:11:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void     launch_commands(t_tree *parsed_params, int8_t parent_type, int8_t *flag);
static void     exec_redirs(t_list *redirs, int heredoc_fileno, int heredoc_fileno2);
static void     wait_for_children(t_tree *parsed_params);
static uint32_t count_cmds(t_tree *node, int n_cmds);

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
        launch_commands(parsed_params, 0, 0);
        wait_for_children(parsed_params);
    }
    dup2(original_stdin, STDIN_FILENO);
    reset_fd(&original_stdin);
}

//inorder traversal search
static void launch_commands(t_tree *parsed_params, int8_t parent_type, int8_t *flag)
{
    t_list  *branches_list;

    if (!parsed_params)
        return ;
    branches_list = parsed_params->branches.branches_list;
    launch_commands(branches_list->prev, parsed_params->type, flag);
    *flag = SECOND_CMD;
    if (parsed_params->type == CMD)
        exec_cmd(parsed_params, parent_type, flag); //fa pipe, fa fork, esegue, ed aspetta settando g_status. se il parent leaf è un pipe, duplica l'input o l'output, altrimenti ignora 
    if ((parsed_params->type == AND && g_status == 0) || (parsed_params->type == OR && g_status != 0))
        return ;
    launch_commands(branches_list->next, parsed_params->type, flag);
    *flag = FIRST_CMD;
}

static void exec_redirs(t_list *redirs, int heredoc_fileno, int heredoc_fileno2)
{
    t_list  *node;
    t_redir *redir;

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
