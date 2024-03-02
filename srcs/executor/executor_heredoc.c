/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 00:33:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int      fill_in_child(char *limiter, int heredoc_fd);
static void     fill_heredoc(char *limiter, int fd);

void create_heredocs(t_tree *tree, int *status)
{
    t_list      *redirs;
    t_redir     *redir;
    int         fd;
    char        *filename;
    t_parser    *elem;

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
            ft_freenull((void **)&filename);
            *status = fill_in_child(redir->filename, fd);
            if (*status != 0)
                return ;
        }
    }
    create_heredocs(tree->left, status);
    create_heredocs(tree->right, status);
}

char    *get_heredoc_filename(int32_t id)
{
    t_data      *data;
    char        *idx;
    char        *filename;
    size_t      size;

    data = get_data();
    idx = ft_utoa((uint32_t)id);
    size = ft_strlen(data->starting_dir) + ft_strlen("/tmp/.heredoc_") + ft_strlen(idx) + 2;
    filename = ft_calloc(size, sizeof(char));
    if (!filename || !idx)
        return (ft_freenull((void **)&idx), ft_freenull((void **)&filename), ft_quit(ERR_MEM, "minishell: failed to allocate memory"), NULL);
    ft_strcpy(filename, data->starting_dir);
    ft_strcat(filename, "/tmp/.heredoc_");
    ft_strcat(filename, idx);
    return (ft_freenull((void **)&idx), filename);
}

static int fill_in_child(char *limiter, int heredoc_fd)
{
    pid_t   pid;
    int     status;

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
    return (status);
}

static void fill_heredoc(char *limiter, int fd)
{
    char    *str;
    char    *tmp;
    size_t  str_len;

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
        tmp = str;
        str = replace_env_vars(str, true);
        ft_putstr_fd(str, fd);
        write(fd, "\n", 1);
        ft_freenull((void **)&tmp);
        ft_freenull((void **)&str);
    }
    ft_freenull((void **)&str);
    free_data();
    exit(0);
}
