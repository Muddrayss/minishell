/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/01/31 22:20:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char    *get_heredoc_filename(int id1, int id2);
static void     fill_heredoc(char *limiter, int fd);

void create_heredocs(t_list *parsed_params)
{
    int         heredoc_fd;
    static int  heredoc_fileno1 = 1;
    int         heredoc_fileno2;
    t_parser    *content;
    t_list      *node;
    t_redir     *redir;

    heredoc_fd = -1;
    while (parsed_params)
    {
        heredoc_fileno2 = 1;
        content = (t_parser *)parsed_params->content;
        node = content->redirs;
        while (node)
        {
            if (*((char *)node->content) == PH_REDIR_STOP)
                heredoc_fileno2++;
            redir = (t_redir *)node->content;
            if (redir->type == REDIR_HEREDOC)
            {
                heredoc_fd = open(get_heredoc_filename(heredoc_fileno1, heredoc_fileno2), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (heredoc_fd == -1)
                    ft_quit(96, NULL);
                fill_heredoc(redir->filename, heredoc_fd);
            }
            node = node->next;
        }
        parsed_params = parsed_params->next;
        heredoc_fileno1++;
    }
    reset_fd(&heredoc_fd); //TODO creare funzione reset fd che chiude un fd se e' diverso da -1 e lo setta a -1 una volta chiuso
}

static char    *get_heredoc_filename(int id1, int id2)
{
    t_data      *data;
    char        *idx1;
    char        *idx2;
    char        *filename;
    size_t      size;

    data = get_data();
    idx1 = ft_itoa(id1);
    idx2 = ft_itoa(id2);
    size = ft_strlen(data->starting_dir) + ft_strlen("/tmp/.heredoc_") + ft_strlen(idx1) + ft_strlen(idx2) + 2;
    filename = ft_calloc(size, sizeof(char));
    if (!filename)
    {
        free(idx1);
        free(idx2);
        ft_quit(22, "failed to allocate memory");
    }
    ft_strlcpy(filename, data->starting_dir, size);
    ft_strlcat(filename, "/tmp/.heredoc_", size);
    ft_strlcat(filename, idx1, size);
    ft_strlcat(filename, ".", size);
    ft_strlcat(filename, idx2, size);
    return (free(idx1), free(idx2), filename);
}

static void fill_heredoc(char *limiter, int fd)
{
    char    *str;
    size_t  str_len;
    size_t  limiter_len;
  
    str = NULL;
    limiter_len = ft_strlen(limiter);
    while (g_status != 130)
    {
        init_in_cmd_signals();
        str = readline("> ");
        if (!str || g_status == 130)
            break ;
        str_len = ft_strlen(str);
        if (ft_strncmp(limiter, str, MAX(str_len, limiter_len)) == 0)
            break ;
        replace_env_vars(&str);
        ft_putstr_fd(str, fd);
        ft_putchar_fd('\n', fd);
        free(str);
        str = NULL; //per evitare la double free
    }
    free(str);
}

int get_matching_heredoc(int id1, int id2)
{
    int fd;

    fd = open(get_heredoc_filename(id1, id2), O_RDONLY, 0644);
    if (fd == -1)
        ft_quit(28, NULL);
    return (fd);
}