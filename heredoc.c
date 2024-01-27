/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/01/27 20:11:08 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

bool is_heredoc(t_list *redirs)
{
    t_list  *node;
    t_redir *redir;

    node = redirs;
    while (node)
    {
        redir = (t_redir *)node->content;
        if (redir->type == REDIR_HEREDOC)
            return (true);
        node = node->next;
    }
    return (false);
}

char    *get_filename(int id1, int id2, t_data *data)
{
    char        *idx1;
    char        *idx2;
    char        *filename;
    size_t      size;

    idx1 = ft_itoa(id1);
    idx2 = ft_itoa(id2);
    size = ft_strlen(data->starting_dir) + ft_strlen("/tmp/.heredoc_") + ft_strlen(idx1) + ft_strlen(idx2) + 2;
    filename = ft_calloc(size, sizeof(char));
    if (!filename)
    {
        free(idx1);
        free(idx2);
        ft_quit(22, "failed to allocate memory", data);
    }
    ft_strlcpy(filename, data->starting_dir, size);
    ft_strlcat(filename, "/tmp/.heredoc_", size);
    ft_strlcat(filename, idx1, size);
    ft_strlcat(filename, ".", size);
    ft_strlcat(filename, idx2, size);
    return (free(idx1), free(idx2), filename);
}

void fill_heredoc(char *limiter, int fd)
{
    char    *str;
    size_t  str_len;
    size_t  limiter_len;
  
    g_signals.in_heredoc = 1;
    str = NULL;
    limiter_len = ft_strlen(limiter);
    while (!g_signals.sigint)
    {
        str = readline("> ");
        if (!str)
            break ;
        //TODO gestire caso in cui str ha una env var con $
        str_len = ft_strlen(str);
        if (ft_strncmp(limiter, str, MAX(str_len, limiter_len)) == 0)
            break ;
        ft_putstr_fd(str, fd);
        ft_putchar_fd('\n', fd);
        free(str);
        str = NULL; //per evitare la double free
    }
    free(str);
    g_signals.in_heredoc = 0;
}