/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 15:58:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static uint8_t  fill_in_child(const char *const limiter, const uint16_t heredoc_fd);
static void     fill_heredoc(const char *const limiter, const uint16_t fd);

void create_heredocs(const t_tree *const tree, uint8_t *const status)
{
    t_parser    *elem;
    t_list      *redirs;
    t_redir     *redir;
    char        *filename;
    uint16_t    fd;

    if (!tree || *status != 0)
        return ;
    elem = (t_parser *)tree->content;
    if (elem->type == CMD)
    {
        redirs = (t_list *)elem->cmd->redirs;
        while (redirs)
        {
            redir = (t_redir *)redirs->content;
            redirs = redirs->next;
            if (redir->type != REDIR_HEREDOC)
                continue ;
            filename = get_heredoc_filename(redir->heredoc_fileno);
            fd = open_p(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            free_and_null((void **)&filename);
            *status = fill_in_child(redir->filename, fd);
            if (*status != 0)
                return ;
        }
    }
    create_heredocs(tree->left, status);
    create_heredocs(tree->right, status);
}

char    *get_heredoc_filename(const uint16_t id)
{
    t_data      *data;
    char        *idx;
    char        *filename;
    uint16_t    size;

    data = get_data();
    idx = ft_itoa((uint16_t)id);
    size = ft_strlen(data->starting_dir) + ft_strlen(idx) + 16;
    filename = ft_calloc(size, sizeof(char));
    if (!filename || !idx)
        return (free_and_null((void **)&idx), free_and_null((void **)&filename), ft_quit(ERR_MEM, "minishell: failed to allocate memory"), NULL);
    ft_strcpy(filename, data->starting_dir);
    ft_strcat(filename, "/tmp/.heredoc_");
    ft_strcat(filename, idx);
    return (free_and_null((void **)&idx), filename);
}

static uint8_t fill_in_child(const char *const limiter, const uint16_t heredoc_fd)
{
    pid_t       pid;
    int32_t     status;

    pid = fork_p();
    if (pid == 0)
    {
        set_signals(S_HEREDOC, false);
        fill_heredoc(limiter, heredoc_fd);
    }
    else
    {
        waitpid_p(pid, &status, 0);
        status = WEXITSTATUS(status);
    }
    return ((uint8_t)status);
}

static void fill_heredoc(const char *const limiter, const uint16_t fd)
{
    char        *str;
    uint16_t    str_len;

    str = NULL;
    while (true)
    {
        str = readline("> ");
        if (!str)
        {
            ft_putstr_fd("\n", STDOUT_FILENO); //altrimenti ctrl+d non va a capo
            break ;
        }
        str_len = ft_strlen(str);
        if (ft_strncmp(limiter, str, str_len + 1) == 0)
            break ;
        replace_env_vars(&str, true);
        ft_putstr_fd(str, fd);
        write(fd, "\n", 1);
        free_and_null((void **)&str);
    }
    free_and_null((void **)&str);
    free_data();
    exit(0);
}
