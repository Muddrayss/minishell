/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/01/25 16:17:45 by egualand         ###   ########.fr       */
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

char    *get_filename(int id, t_data *data)
{
    char        *idx;
    char        *tmp;
    char        *filename;

    idx = ft_itoa(id);
    tmp = ft_strjoin(data->starting_dir, "/tmp/.heredoc_");
    filename = ft_strjoin(tmp, idx);
    free(tmp);
    free(idx);
    if (!filename)
        ft_quit(22, "failed to allocate memory", data);
    return (filename);
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