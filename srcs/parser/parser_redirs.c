/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:16:55 by craimond          #+#    #+#             */
/*   Updated: 2024/02/27 19:21:30 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char     *remove_fd_num(char *str, uint32_t idx_redir);
static char     *remove_filename(char *str, uint32_t idx_redir);
static void     fill_redir_input(t_list **redirs, char *str, uint32_t i);
static void     fill_redir_heredoc(t_list **redirs, char *str, uint32_t i, int32_t heredoc_fileno);
static void     fill_redir_output(t_list **redirs, char *str, uint32_t i, bool is_append);
static int32_t  get_fd_num(char *str, uint32_t i);
static char     *get_filename(char *str, uint32_t idx_redir);
static t_redir  *init_redir(void);

t_list  *fill_redirs(char *cmd_str)
{
    t_list          *redirs;
    uint32_t        i;
    static int32_t  heredoc_fileno = 0;
    char            master_quote;

    if (!cmd_str)
        return (NULL);
    i = 0;
    redirs = NULL;
    master_quote = '\0';
    while (cmd_str[i])
    {
        if (!master_quote && (is_quote(cmd_str[i])))
            master_quote = cmd_str[i];
        else if (master_quote && cmd_str[i] == master_quote)
            master_quote = '\0';
        if (!master_quote)
        {
            if (cmd_str[i] == '<')
            {
                if (cmd_str[i + 1] == '<')
                    fill_redir_heredoc(&redirs, cmd_str, ++i, heredoc_fileno);
                else
                    fill_redir_input(&redirs, cmd_str, i);
            }
            else if (cmd_str[i] == '>')
            {
                if (cmd_str[i + 1] == '>')
                    fill_redir_output(&redirs, cmd_str, ++i, true);
                else
                    fill_redir_output(&redirs, cmd_str, i, false);
            }
        }
        i++;
    }
    return (heredoc_fileno++, lstreverse(&redirs), redirs);
}

char    *clear_redirs(t_list *redirs, char *cmd_str)
{
    uint32_t    i;
    t_redir     *redir;
    char        master_quote;
    uint32_t    to_skip;
    char        *tmp;

    if (!cmd_str || !redirs)
        return (cmd_str);
    master_quote = '\0';
    i = -1;
    while (cmd_str[++i])
    {
        if (!master_quote && (cmd_str[i] == '\'' || cmd_str[i] == '"'))
            master_quote = cmd_str[i];
        else if (master_quote && cmd_str[i] == master_quote)
            master_quote = '\0';
        if (!master_quote)
        {
            if (cmd_str[i] == '<' || cmd_str[i] == '>')
            {
                redir = (t_redir *)redirs->content;
                if (redir->filename)
                    cmd_str = remove_filename(cmd_str, i);
                cmd_str = remove_fd_num(cmd_str, i);
                to_skip = 1;
                if (cmd_str[i + 1] == '<' || cmd_str[i + 1] == '>')
                    to_skip++;
                tmp = cmd_str;
                cmd_str = (char *)calloc_p(ft_strlen(cmd_str) - to_skip + 1, sizeof(char));
                ft_strlcpy(cmd_str, tmp, i);
                ft_strcat(cmd_str, tmp + i + to_skip);
                free(tmp);
                redirs = redirs->next;
                i--;
            }
        }
    }
    return (cmd_str);
}

static void fill_redir_heredoc(t_list **redirs, char *str, uint32_t i, int32_t heredoc_fileno)
{
    t_redir *redir;

    redir = init_redir();
    redir->type = REDIR_HEREDOC;
    redir->filename = get_filename(str, i);
    redir->heredoc_fileno = heredoc_fileno;
    lstadd_front(redirs, lstnew_p(redir));
}

static void    fill_redir_input(t_list **redirs, char *str, uint32_t i)
{
    t_redir         *redir;

    redir = init_redir();
    redir->type = REDIR_INPUT_FD;
    redir->fds[0] = get_fd_num(str, i);
    if (redir->fds[0] == -42)
    {
        redir->type = REDIR_INPUT;
        redir->filename = get_filename(str, i);
    }
    lstadd_front(redirs, lstnew_p(redir));
}

static void     fill_redir_output(t_list **redirs, char *str, uint32_t i, bool is_append)
{
    t_redir *redir;

    redir = init_redir();
    redir->type = REDIR_APPEND_FD * (is_append) + REDIR_OUTPUT_FD * (!is_append);
    redir->fds[1] = get_fd_num(str, i);
    if (redir->fds[1] == -42)
    {
        redir->type = REDIR_APPEND * (is_append) + REDIR_OUTPUT * (!is_append);
        redir->filename = get_filename(str, i);
    }
    if (redir->fds[0] == -42)
        redir->fds[0] = STDOUT_FILENO;
    lstadd_front(redirs, lstnew_p(redir));
}

static t_redir *init_redir(void)
{
    t_redir *redir;

    redir = malloc_p(sizeof(t_redir));
    redir->fds[0] = -42;
    redir->fds[1] = -42;
    redir->filename = NULL;
    redir->heredoc_fileno = -1;
    redir->type = -1;
    return (redir);
}

static char *get_filename(char *str, uint32_t idx_redir)
{
	char 		*filename;
	uint32_t 	len;
	uint32_t 	i;
	
	filename = NULL;
	i = idx_redir + 1;
	while (str[i] != '\0' && is_shell_space(str[i]))
		i++;
	len = 0;
	while (str[i + len] && !is_shell_space(str[i + len]) && !is_quote(str[i + len]))
		len++;
	filename = calloc_p(len + 1, sizeof(char));
	ft_strlcpy(filename, &str[i], len + 1);
	return (filename);
}

static int32_t get_fd_num(char *str, uint32_t i)
{
    int32_t     num;

    num = -42;
    i--;
    while (str[i] && ft_isdigit(str[i]))
        i--;
    if (ft_isdigit(str[i + 1]))
        num = ft_atou(&str[i + 1]);
    return (num);
}

static char *remove_fd_num(char *str, uint32_t idx_redir)
{
    char     *new_str;
    uint32_t start;
    uint32_t end;

    start = idx_redir + 1 + (str[idx_redir + 1] == '<' || str[idx_redir + 1] == '>');
    end = start;
    while (str[end] && ft_isdigit(str[end]))
        end++;
    new_str = (char *)malloc_p(sizeof(char) * (ft_strlen(str) - (end - start) + 1));
    ft_strlcpy(new_str, str, start + 1);
    ft_strcat(new_str, &str[end]);
    return(free(str), new_str);
}

static char  *remove_filename(char *str, uint32_t idx_redir)
{
    char        *new_str;
    uint32_t    start;
    uint32_t    end;

    start = idx_redir + 1 + (str[idx_redir + 1] == '<' || str[idx_redir + 1] == '>');
    end = start;
    while (str[end] && is_shell_space(str[end]))
        end++;
    while (str[end] && !is_shell_space(str[end]))
        end++;
    new_str = (char *)malloc_p(sizeof(char) * (ft_strlen(str) - (end - start) + 1));
    ft_strlcpy(new_str, str, start + 1);
    ft_strcat(new_str, &str[end]);
    return (free(str), new_str);
}