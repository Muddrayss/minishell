/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/02/02 17:19:07 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char     *get_heredoc_filename(int id1, int id2);
static uint32_t count_heredocs(t_tree *node, uint32_t n_heredocs);
static char     **get_limiters_array(t_tree *node);
static void     fill_limiters_array(t_tree *node, char **limiters_array, uint32_t i);
static void     fill_in_child(char *limiter, int heredoc_fd);
static void     fill_heredoc(char *limiter, int fd);

void create_heredocs(t_tree *tree, uint32_t heredoc_fileno1)
{
    int         heredoc_fd;
    uint32_t    heredoc_fileno2;
    t_redir     *redir;
    char        **limiters_array;
    uint32_t    n_heredocs;
    uint32_t    i;

    i = 0;
    limiters_array = get_limiters_array(tree);
    while (limiters_array[n_heredocs])
        n_heredocs++;
    heredoc_fileno2 = 1;
    heredoc_fd = -1;
    while (i < n_heredocs)
    {
        heredoc_fd = open_p(get_heredoc_filename(heredoc_fileno1, heredoc_fileno2++), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        fill_in_child(limiters_array[i++], heredoc_fd);
        if (g_status == 130)
        {
            reset_fd(&heredoc_fd);
            break ;
        }
    }
    free_matrix(limiters_array);
    reset_fd(&heredoc_fd);
}

static char    **get_limiters_array(t_tree *node)
{
    uint32_t    n_heredocs;
    char        **limiters_array;

    n_heredocs = count_heredocs(node, 0);
    limiters_array = (char **)malloc(sizeof(char *) * (n_heredocs + 1));
    if (!limiters_array)
        ft_quit(8, "failed to allocate memory");
    limiters_array[n_heredocs] = NULL;
    fill_limiters_array(node, limiters_array, 0);
    return (limiters_array);
}

static void fill_limiters_array(t_tree *node, char **limiters_array, uint32_t i)
{
    t_list      *redirs;
    t_list      *branches_list;
    t_redir     *content;

    if (!node)
        return ;
    if (node->type == CMD)
    {
        redirs = node->cmd.redirs;
        while (redirs)
        {
            content = (t_redir *)redirs->content;
            if (content->type == REDIR_HEREDOC)
                limiters_array[i++] = content->filename;
            redirs = redirs->next;
        }
    }
    branches_list = node->branches.branches_list;
    fill_limiters_array(branches_list->prev, limiters_array, i);
    fill_limiters_array(branches_list->next, limiters_array, i);
}

static uint32_t count_heredocs(t_tree *node, uint32_t n_heredocs)
{
    t_list      *redirs;
    t_list      *branches_list;

    if (!node)
        return (n_heredocs);
    if (node->type == CMD)
    {
        redirs = node->cmd.redirs;
        while (redirs)
        {
            n_heredocs += (((t_redir *)(redirs->content))->type == REDIR_HEREDOC);
            redirs = redirs->next;
        }
    }
    branches_list = node->branches.branches_list;
    n_heredocs += count_heredocs(branches_list->prev, n_heredocs);
    n_heredocs += count_heredocs(branches_list->next, n_heredocs);
    return (n_heredocs);
}

//usare strcat invece che strlcat
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
    size = ft_strlen(data->starting_dir) + ft_strlen("./tmp.heredoc_") + ft_strlen(idx1) + ft_strlen(idx2) + 2;
    filename = ft_calloc(size, sizeof(char));
    if (!filename || !idx1 || !idx2)
    {
        //complex return con tutti i free e ft_quit
        free(idx1);
        free(idx2);
        free(filename);
        ft_quit(22, "failed to allocate memory");
    }
    ft_strcpy(filename, data->starting_dir);
    ft_strcat(filename, HEREDOC_DIR);
    ft_strcat(filename, idx1);
    ft_strcat(filename, ".");
    ft_strcat(filename, idx2);
    return (free(idx1), free(idx2), filename);
}

static void fill_in_child(char *limiter, int heredoc_fd)
{
    pid_t   pid;
    int     status;

    set_sighandler(SIG_IGN, SIG_IGN);
    pid = fork_p();
    if (pid == 0)
    {
        set_sighandler(&display_and_quit_signal, SIG_IGN);
        fill_heredoc(limiter, heredoc_fd);
    }
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
        if (ft_strncmp(limiter, str, MAX(str_len, limiter_len)) == 0)
            break ;
        replace_env_vars(&str);
        ft_putstr_fd(str, fd);
        ft_putchar_fd('\n', fd);
        free(str);
        str = NULL; //per evitare la double free
    }
    free(str);
    exit(0);
}

int get_matching_heredoc(int id1, int id2)
{
    int fd;

    fd = open_p(get_heredoc_filename(id1, id2), O_RDONLY, 0644);
    return (fd);
}
