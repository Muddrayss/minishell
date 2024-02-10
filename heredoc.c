/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/02/10 18:32:27 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void     fill_in_child(char *limiter, int heredoc_fd);
static void     fill_heredoc(char *limiter, int fd);

bool create_heredocs(t_tree *tree)
{
    t_list *redirs;
    t_redir *redir;
    int heredoc_fd;
    bool success;

    success = true;
    if (!tree || g_status == 130)
        return (false);

    if (tree->type == CMD)
    {
        redirs = (t_list *)tree->cmd->redirs;
        while (redirs)
        {
            redir = (t_redir *)redirs->content;
            if (redir->type == REDIR_HEREDOC)
            {
                heredoc_fd = open_p(get_heredoc_filename(redir->heredoc_fileno), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                fill_in_child(redir->filename, heredoc_fd);
                if (g_status == 130)
                {
                    reset_fd(&heredoc_fd);
                    success = false;
                    break;
                }
            }
            redirs = redirs->next;
        }
    }
    if (tree->left && !create_heredocs(tree->left))
        success = false;
    if (tree->right && !create_heredocs(tree->right))
        success = false;
    return (success);
}


//usare strcat invece che strlcat
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

static void fill_in_child(char *limiter, int heredoc_fd)
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
        waitpid_p(pid, &status, 0);
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
        str = readline("> ");
        if (!str || g_status == 130)
        {
            ft_putstr_fd("\n", STDOUT_FILENO);
            break ;
        }
        str_len = ft_strlen(str);
        //se aggiungessimo il \n al limiter basterebbe fare strncmp con limiter_len + 1
        if (ft_strncmp(limiter, str, MAX(str_len, limiter_len)) == 0)
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
