/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:16:55 by craimond          #+#    #+#             */
/*   Updated: 2024/02/27 23:53:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char     *remove_chars(char *str, bool *to_remove_array);
static void     remove_fd_num(char *str, uint32_t i, bool *to_remove_array);
static uint32_t remove_filename(char *str, uint32_t i, bool *to_remove_array);
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
    bool        *to_remove_array;
    t_redir     *redir;
    char        master_quote;

    if (!cmd_str || !redirs)
        return (cmd_str);
    to_remove_array = (bool *)calloc_p(ft_strlen(cmd_str), sizeof(bool));
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
                to_remove_array[i] = true;
                to_remove_array[i + 1] = (cmd_str[i + 1] == '<' || cmd_str[i + 1] == '>');
                if (redir->filename)
                    i = remove_filename(cmd_str, i, to_remove_array);
                if (redir->fds[0] != -42)
                    remove_fd_num(cmd_str, i, to_remove_array);
            }
        }
    }
    return (remove_chars(cmd_str, to_remove_array));
}

static char *remove_chars(char *str, bool *to_remove_array)
{
    uint32_t    to_remove_len;
    char        *new_str;
    uint32_t    i;
    uint32_t    j;

    i = -1;
    to_remove_len = 0;
    while (str[++i])
        to_remove_len += to_remove_array[i];
    new_str = (char *)malloc_p(sizeof(char) * (ft_strlen(str) - to_remove_len + 1));
    i = -1;
    j = 0;
    while (str[++i])
        if (!to_remove_array[i])
            new_str[j++] = str[i];
    new_str[i] = '\0';
    return (new_str);
}

static void remove_fd_num(char *str, uint32_t i, bool *to_remove_array)
{
    i--;
    while (i > 0 && ft_isdigit(str[i]))
        to_remove_array[i--] = true;
}

static uint32_t remove_filename(char *str, uint32_t i, bool *to_remove_array)
{
    i += 1 + (str[i + 1] == '<' || str[i + 1] == '>');
    while (str[i] && is_shell_space(str[i]))
        to_remove_array[i++] = true;
    while (str[i] && !is_shell_space(str[i])) // && !is_quote(str[i]))
        to_remove_array[i++] = true;
    return (i - 1);
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
