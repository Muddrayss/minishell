/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/27 18:44:41 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void create_heredocs(t_list *parsed_params, t_data *data);
static int parent(int fds[], t_data *data);
static bool is_last_subcmd(char *cmd_str);
static void child(t_parser *content, int fds[], bool is_last, int original_stdin, int heredoc_fileno, t_data *data);
static void exec_redirs(t_list *redirs, t_data *data);
// static void resume(t_list *node);
static char *ft_strdup_until(char *str, char c, t_data *data);
static t_list *ft_lstdup_until(t_list *lst, void *stop, t_data *data);
static void wait_for_children(t_list *parsed_params);
static int get_matching_heredoc(int id1, int id2, t_data *data);

void executor(t_list *parsed_params, t_data *data)
{
    t_parser        *content;
    t_list          *node;
    int             fds[3];
    int             prev_out_fd;
    int             original_stdin;
    static int      heredoc_fileno = 1;

    original_stdin = dup(STDIN_FILENO);
    if (original_stdin == -1)
        ft_quit(24, NULL, data);
    create_heredocs(parsed_params, data);
    prev_out_fd = -1;
    node = parsed_params;
    printf("Starting node\n");
    while (node)
    {
        content = (t_parser *)node->content;
        if (pipe(fds) == -1)
            ft_quit(18, NULL, data);
        fds[2] = prev_out_fd;
        content->pid = fork();
        if (content->pid == -1)
            ft_quit(19, NULL, data);
        if (content->pid == 0)
            child(content, fds, node->next == NULL, original_stdin, heredoc_fileno++, data);
        else
            prev_out_fd = parent(fds, data);
        node = node->next;
    }
    printf("Finishing node\n");
    // resume(parsed_params);
    wait_for_children(parsed_params);
    if (dup2(original_stdin, STDIN_FILENO) == -1 || close(original_stdin) == -1)
        ft_quit(24, NULL, data);
}


static void create_heredocs(t_list *parsed_params, t_data *data)
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
                heredoc_fd = open(get_filename(heredoc_fileno1, heredoc_fileno2++, data), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (heredoc_fd == -1)
                    ft_quit(96, NULL, data);
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

static int parent(int fds[], t_data *data)
{
    int             status;
    
    if (close(fds[1]) == -1 || (fds[2] != -1 && close(fds[2]) == -1))
        ft_quit(29, NULL, data);
    wait3(&status, WUNTRACED, NULL);
    if (!WIFSTOPPED(status) && !WIFEXITED(status))
    {
        printf("kill all\n");
        kill(0, SIGINT);
        exit(0);
    }
    return (fds[0]);
}

static void child(t_parser *content, int fds[], bool is_last, int original_stdin, int heredoc_fileno, t_data *data)
{
    char            *new_cmd_str;
    t_list          *new_redirs;
    static char     ph_redir_stop = PH_REDIR_STOP;
    int             i;
    int             heredoc_fileno2;
    pid_t           pid;

    if (fds[2] != -1 && (dup2(fds[2], STDIN_FILENO) == -1 || close(fds[2]) == -1))
        ft_quit(25, NULL, data);
    i = 0;
    heredoc_fileno2 = 1;
    while (content->cmd_str[i] != '\0')
    {
        new_cmd_str = ft_strdup_until(content->cmd_str, PH_SEMICOLON, data); //fino a '\0' o PH_SEMICOLON
        new_redirs = ft_lstdup_until(content->redirs, &ph_redir_stop, data);  //fino a NULL o PH_REDIR_STOP
        pid = fork();
        if (pid == -1)
            ft_quit(26, NULL, data);
        if (pid == 0)
        {
            if (new_redirs)
                exec_redirs(new_redirs, data);
            if (is_heredoc(new_redirs))
                dup2(get_matching_heredoc(heredoc_fileno, heredoc_fileno2++, data), STDIN_FILENO);
            if (is_last_subcmd(content->cmd_str))
            {
                if (close(fds[0]) == -1 || (!is_last && dup2(fds[1], STDOUT_FILENO) == -1) || close(fds[1]) == -1)
                    ft_quit(27, NULL, data);
            }
            printf("executing: %s\n", new_cmd_str);
            exec(ft_getenv(data, "PATH"), new_cmd_str, data);
        }
        else
        {
            printf("aspettando pid: %d\n", pid);
            waitpid(pid, NULL, 0);
            printf("sbloccato pid: %d\n", pid);
            i += ft_strlen(new_cmd_str);
            free(new_cmd_str);
            if (dup2(original_stdin, STDIN_FILENO) == -1)
                ft_quit(24, NULL, data);
        }
    }
}

static char *ft_strdup_until(char *str, char c, t_data *data)
{
    char                    *new_str;
    size_t                  size;
    static unsigned int     i = 0;

    while (str[i] && str[i] != c)
        i++;
    size = i + 1;
    new_str = (char *)ft_calloc(size, sizeof(char));
    if (!new_str)
       ft_quit(15, "failed to allocate memory", data);
    ft_strlcpy(new_str, str, size);
    return (new_str);
}

static t_list *ft_lstdup_until(t_list *lst, void *stop, t_data *data)
{
    t_list                  *new_lst;
    t_list                  *node;
    t_list                  *new_node;
    static  unsigned int    start = 0;
    unsigned int            i;

    i = 0;
    new_lst = NULL;
    node = lst;
    while (i < start && node)
    {
        node = node->next;
        i++;
    }
    while (node && *((char *)(node->content)) != *((char *)stop))
    {
        new_node = ft_lstnew(node->content);
        if (!new_node)
            ft_quit(16, "failed to allocate memory", data);
        ft_lstadd_back(&new_lst, new_node);
        node = node->next;
    }
    return (new_lst);
}

static int get_matching_heredoc(int id1, int id2, t_data *data)
{
    int fd;

    fd = open(get_filename(id1, id2, data), O_RDONLY);
    if (fd == -1)
        ft_quit(28, NULL, data);
    return (fd);
}

static bool is_last_subcmd(char *cmd_str)
{
    static unsigned int i = 0;

    while (cmd_str[i])
    {
        if (cmd_str[i] == PH_SEMICOLON)
            return (false);
        i++;
    }
    return (true);
}

static void exec_redirs(t_list *redirs, t_data *data)
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
                    ft_quit(21, NULL, data);
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
                    ft_quit(22, NULL, data);
            }
        }
        node = node->next;
    }
    if (dup2(redir->fds[0], STDIN_FILENO) == -1 || (redir->fds[0] != STDIN_FILENO && close(redir->fds[0]) == -1))
        ft_quit(23, NULL, data);
    if (dup2(redir->fds[1], STDOUT_FILENO) == -1 || (redir->fds[1] != STDOUT_FILENO && close(redir->fds[1]) == -1))
        ft_quit(24, NULL, data);
}

// static void resume(t_list *node)
// {
//     t_parser        *content;

//     while (node)
//     {
//         content = (t_parser *)node->content;
//         kill(content->pid, SIGCONT);
//         node = node->next;
//     }
// }

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
