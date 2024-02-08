/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/02/09 00:08:01 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static uint32_t count_heredocs(t_tree *node, uint32_t n_heredocs);
static char     **get_limiters_array(t_tree *node);
static void     fill_limiters_array(t_tree *node, char **limiters_array, uint32_t i);
static void     fill_in_child(char *limiter, int heredoc_fd);
static void     fill_heredoc(char *limiter, int fd);

void create_heredocs(t_tree *tree)
{
    static uint32_t  heredoc_fileno = 0;
    int32_t          heredoc_fd;
    char             **limiters_array;
    uint32_t         i;

    limiters_array = get_limiters_array(tree);
    heredoc_fd = -42;
    i = 0;
    while (limiters_array[i])
    {
        heredoc_fd = open_p(get_heredoc_filename(heredoc_fileno++), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        fill_in_child(limiters_array[i++], heredoc_fd);
        if (g_status == 130)
        {
            reset_fd(&heredoc_fd);
            break ;
        }
    }
    ft_freematrix(limiters_array);
    reset_fd(&heredoc_fd);
}

static char    **get_limiters_array(t_tree *node)
{
    char        **limiters_array;
    uint32_t    n_heredocs;

    n_heredocs = count_heredocs(node, 0);
    limiters_array = (char **)malloc_p(sizeof(char *) * (n_heredocs + 1));
    limiters_array[n_heredocs] = NULL;
    fill_limiters_array(node, limiters_array, 0);
    return (limiters_array);
}

//inorder traversal search (L, N, R)
static void fill_limiters_array(t_tree *node, char **limiters_array, uint32_t i)
{
    t_list      *redirs;
    t_redir     *content;

    if (!node)
        return ;
    fill_limiters_array(node->left, limiters_array, i);
    if (node->type == CMD)
    {
        redirs = node->cmd->redirs;
        while (redirs)
        {
            content = (t_redir *)redirs->content;
            if (content->type == REDIR_HEREDOC)
                limiters_array[i++] = content->filename;
            redirs = redirs->next;
        }
    }
    fill_limiters_array(node->right, limiters_array, i);
}

static uint32_t count_heredocs(t_tree *node, uint32_t n_heredocs)
{
    t_list      *redirs;

    if (!node)
        return (n_heredocs);
    if (node->type == CMD)
    {
        redirs = node->cmd->redirs;
        while (redirs)
        {
            n_heredocs += (((t_redir *)(redirs->content))->type == REDIR_HEREDOC);
            redirs = redirs->next;
        }
    }
    n_heredocs += count_heredocs(node->left, n_heredocs);
    n_heredocs += count_heredocs(node->right, n_heredocs);
    return (n_heredocs);
}

//usare strcat invece che strlcat
char    *get_heredoc_filename(uint32_t id)
{
    t_data      *data;
    char        *idx;
    char        *filename;
    size_t      size;

    data = get_data();
    idx = ft_utoa(id);
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
        fill_heredoc(limiter, heredoc_fd);
    else
    {
        waitpid_p(pid, &status, 0);
        if (WEXITSTATUS(status) == SIGINT)
            g_status = 130;
        else if (g_status == 130)
            g_status = 0;
    }
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
