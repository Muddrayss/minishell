/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/06 12:13:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void     launch_commands(t_tree *parsed_params, int8_t parent_type, int8_t *flag);
static void     exec_redirs(t_list *redirs, int heredoc_fileno, int heredoc_fileno2);
static void     exec_cmd();
static void     wait_for_children(t_tree *parsed_params);
static uint32_t count_cmds(t_tree *node, int n_cmds);

//E" NORMALE CHE CRASHI NELL'EXECUTOR!!!! ANCORA NON E' STATO AGGIUSTATO ALL'ALBERO
void    executor(t_tree *parsed_params)
{
    int             original_stdin;
    static int      heredoc_fileno1 = 1;

    original_stdin = dup_p(STDIN_FILENO);
    create_heredocs(parsed_params, heredoc_fileno1);
    if (g_status != 130)
    {
        set_sighandler(&newline_signal, SIG_IGN);
        launch_commands(parsed_params, 0, 0);
        wait_for_children(parsed_params);
    }
    dup2(original_stdin, STDIN_FILENO);
    reset_fd(&original_stdin);
}

//inorder traversal search (L, N, R)
static void launch_commands(t_tree *parsed_params, int8_t parent_type, int8_t *flag)
{
    if (!parsed_params)
        return ;
    launch_commands(parsed_params->left, parsed_params->type, flag);
    *flag = SECOND_CMD;
    if (parsed_params->type == CMD)
        exec_cmd(parsed_params, parent_type, flag); //fa pipe, fa fork, esegue, ed aspetta settando g_status. se il parent leaf è un pipe, duplica l'input o l'output, altrimenti ignora 
    if ((parsed_params->type == AND && g_status == 0) || (parsed_params->type == OR && g_status != 0))
        return ; //breaka e non esegue i comandi successivo
    launch_commands(parsed_params->right, parsed_params->type, flag);
    *flag = FIRST_CMD;
}

static void exec_cmd()
{
    //TODO
    exec_redirs(NULL, 0, 0);
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
            redir->filename = replace_env_vars(redir->filename);
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
    if (!node)
        return (n_cmds);
    if (node->type == CMD)
        n_cmds++;
    n_cmds += count_cmds(node->left, 0);
    n_cmds += count_cmds(node->right, 0);
    return (n_cmds);
}
