/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/28 19:41:01 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void create_heredocs(t_list *parsed_params);
static int parent(int fds[]);
static bool check_last_subcmd(char *cmd_str);
static void child(t_parser *content, int fds[], bool is_last, int original_stdin, int heredoc_fileno);
static void exec_redirs(t_list *redirs);
static char *ft_strdup_until(char *str, char c);
static t_list *ft_lstdup_until(t_list *lst, void *stop);
static void wait_for_children(t_list *parsed_params);
static int get_matching_heredoc(int id1, int id2);

void executor(t_list *parsed_params)
{
    t_parser        *content;
    t_list          *node;
    int             fds[3];
    int             prev_out_fd;
    int             original_stdin;
    static int      heredoc_fileno = 1;

    original_stdin = dup(STDIN_FILENO);
    if (original_stdin == -1)
        ft_quit(24, NULL);
    create_heredocs(parsed_params);
    prev_out_fd = -1;
    node = parsed_params;
    while (node)
    {
        content = (t_parser *)node->content;
        if (pipe(fds) == -1)
            ft_quit(18, NULL);
        fds[2] = prev_out_fd;
        content->pid = fork();
        if (content->pid == -1)
            ft_quit(19, NULL);
        if (content->pid == 0)
            child(content, fds, node->next == NULL, original_stdin, heredoc_fileno);
        else
            prev_out_fd = parent(fds);
        node = node->next;
        heredoc_fileno++;
    }
    wait_for_children(parsed_params);
    if (dup2(original_stdin, STDIN_FILENO) == -1 || close(original_stdin) == -1)
        ft_quit(24, NULL);
}


static void create_heredocs(t_list *parsed_params)
{
    int         heredoc_fd;
    static int  heredoc_fileno1 = 1;
    int         heredoc_fileno2;
    t_parser    *content;
    t_list      *node;
    t_redir     *redir;

    while (parsed_params)
    {
        heredoc_fd = -1;
        heredoc_fileno2 = 1;
        content = (t_parser *)parsed_params->content;
        node = content->redirs;
        while (node)
        {
            if (heredoc_fd == -1 || *((char *)node->content) == PH_REDIR_STOP)
            {
                if (heredoc_fd != -1)       
                    node = node->next;
                close(heredoc_fd);
                if (((t_redir *)node->content)->type == REDIR_HEREDOC)
                {
                    heredoc_fd = open(get_filename(heredoc_fileno1, heredoc_fileno2++), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (heredoc_fd == -1)
                        ft_quit(96, NULL);  
                }
            }
            redir = (t_redir *)node->content;
            if (redir->type == REDIR_HEREDOC)
                fill_heredoc(redir->filename, heredoc_fd);
            node = node->next;
        }
        parsed_params = parsed_params->next;
        heredoc_fileno1++;
    }
    close(heredoc_fd);
}

static int parent(int fds[])
{
    int             status;
    
    init_in_cmd_signals();
    if (close(fds[1]) == -1 || (fds[2] != -1 && close(fds[2]) == -1))
        ft_quit(29, NULL);
    wait3(&status, WUNTRACED, NULL);
    if (!WIFSTOPPED(status) && !WIFEXITED(status))
    {
        kill(0, SIGINT);
        exit(0);
    }
    return (fds[0]);
}

static void child(t_parser *content, int fds[], bool is_last, int original_stdin, int heredoc_fileno)
{
    char            *new_cmd_str;
    t_list          *new_redirs;
    static char     ph_redir_stop = PH_REDIR_STOP;
    int             heredoc_fileno2;
    pid_t           pid;
    bool            is_last_subcmd;

    if (fds[2] != -1 && (dup2(fds[2], STDIN_FILENO) == -1 || close(fds[2]) == -1))
        ft_quit(25, NULL);
    heredoc_fileno2 = 1;
    while (1)
    {
        new_cmd_str = ft_strdup_until(content->cmd_str, PH_SEMICOLON); //fino a '\0' o PH_SEMICOLON
        new_redirs = ft_lstdup_until(content->redirs, &ph_redir_stop);  //fino a NULL o PH_REDIR_STOP
        if ((!new_cmd_str || new_cmd_str[0] == '\0') && !new_redirs) //se c'e' una redir la stringa e' vuota ma devi comunque eseguire
            break ;
        is_last_subcmd = check_last_subcmd(content->cmd_str);
        pid = fork();
        if (pid == -1)
            ft_quit(26, NULL);
        if (pid == 0)
        {
            if (new_redirs)
                exec_redirs(new_redirs);
            if (is_heredoc(new_redirs))
            {
                if (dup2(get_matching_heredoc(heredoc_fileno, heredoc_fileno2), STDIN_FILENO) == -1)
                    ft_quit(32, NULL);
            }    
            if (is_last_subcmd)
            {
                if (close(fds[0]) == -1 || (!is_last && dup2(fds[1], STDOUT_FILENO) == -1) || close(fds[1]) == -1)
                    ft_quit(27, NULL);
            }
            exec(ft_getenv("PATH"), new_cmd_str);
        }
        else
        {
            if (is_heredoc(new_redirs))
                heredoc_fileno2++;
            waitpid(pid, NULL, 0);
            free(new_cmd_str);
            if (dup2(original_stdin, STDIN_FILENO) == -1)
                ft_quit(24, NULL);
        }
    }
    exit(0);
}

static char *ft_strdup_until(char *str, char c)
{
    char                    *new_str;
    size_t                  size;
    static unsigned int     i = 0;

    size = 0;
    while (str[i + size] && str[i + size] != c)
        size++;
    size++;
    new_str = (char *)ft_calloc(size, sizeof(char));
    if (!new_str)
       ft_quit(15, "failed to allocate memory");
    ft_strlcpy(new_str, str + i, size);
    i += size;
    return (i++, new_str);
}

static t_list *ft_lstdup_until(t_list *lst, void *stop)
{
    t_list                  *new_lst;
    static t_list           *node;
    static bool             over = false;
    t_list                  *new_node;

    if (over == true)
        return (NULL);
    if (!node)
        node = lst;
    new_lst = NULL;
    while (node && *((char *)(node->content)) != *((char *)stop))
    {
        new_node = ft_lstnew(node->content);
        if (!new_node)
            ft_quit(16, "failed to allocate memory");
        ft_lstadd_back(&new_lst, new_node);
        node = node->next;
    }
    if (node)
        node = node->next;
    else
        over = true;
    return (new_lst);
}

static int get_matching_heredoc(int id1, int id2)
{
    int fd;

    fd = open(get_filename(id1, id2), O_RDONLY);
    if (fd == -1)
        ft_quit(28, NULL);
    return (fd);
}

static bool check_last_subcmd(char *cmd_str)
{
    static unsigned int i = 0;

    while (cmd_str[i])
    {
        if (cmd_str[i] == PH_SEMICOLON)
            return (i++, false);
        i++;
    }
    return (i++, true);
}

static void exec_redirs(t_list *redirs)
{
    t_list          *node;
    t_redir         *redir;

    node = redirs;
    while (node)
    {
        redir = (t_redir *)node->content;
        if (redir->fds[0] == -42)
        {
            if (redir->type == REDIR_INPUT)
            {
                redir->fds[0] = open(redir->filename, O_RDONLY, 0644);
                if (redir->fds[0] == -1)
                    ft_quit(21, NULL);
            }
        }
        else if (redir->fds[1] == -42)
        {
            if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
            {
                if ((redir->type == REDIR_OUTPUT))
                    redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                else if (redir->type == REDIR_APPEND)
                    redir->fds[1] = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (redir->fds[1] == -1)
                    ft_quit(22, NULL);
            }
        }
        node = node->next;
    }
    if (redir->fds[0] != -42 && (dup2(redir->fds[0], STDIN_FILENO) == -1 || (redir->fds[0] != STDIN_FILENO && close(redir->fds[0]) == -1)))
        ft_quit(26, NULL);
    if (dup2(redir->fds[1], STDOUT_FILENO) == -1 || (redir->fds[1] != STDOUT_FILENO && close(redir->fds[1]) == -1))
        ft_quit(24, NULL);
}

static void wait_for_children(t_list *parsed_params)
{
    t_parser        *content;
    t_list          *node;
    int             status;

    node = parsed_params;
    while (node)
    {
        content = (t_parser *)node->content;
        waitpid(content->pid, &status, 0);
        node = node->next;
    }
}
