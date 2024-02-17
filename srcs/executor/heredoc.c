/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/02/17 14:30:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int      fill_in_child(char *limiter, int heredoc_fd);
static void     fill_heredoc(char *limiter, int fd);

void create_heredocs(t_tree *tree, int *status)
{
    t_list  *redirs;
    t_redir *redir;
    int     fd;
    char    *filename;

    if (!tree || *status != 0)
        return ;
    if (tree->type == CMD)
    {
        redirs = (t_list *)tree->cmd->redirs;
        while (redirs)
        {
            redir = (t_redir *)redirs->content;
            if (redir->type == REDIR_HEREDOC)
            {
                filename = get_heredoc_filename(redir->heredoc_fileno);
                fd = open_p(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                *status = fill_in_child(redir->filename, fd);
                if (*status != 0)
                    return ;
            }
            redirs = redirs->next;
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
        return (free(idx), free(filename), ft_quit(ERR_MALLOC, "failed to allocate memory"), NULL);
    ft_strcpy(filename, data->starting_dir);
    ft_strcat(filename, "/tmp/.heredoc_");
    ft_strcat(filename, idx);
    return (free(idx), filename);
}

static int fill_in_child(char *limiter, int heredoc_fd)
{
    pid_t   pid;
    int     status;

    pid = fork_p();
    if (pid == 0)
    {
        set_signals(S_HEREDOC);
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
    size_t  str_len;
  
    str = NULL;
    while (1)
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
        str = replace_env_vars(str);
        ft_putstr_fd(str, fd);
        write(fd, "\n", 1);
        free(str);
        str = NULL; //per evitare la double free
    }
    free(str);
    exit(0);
}
