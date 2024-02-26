/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:16:55 by craimond          #+#    #+#             */
/*   Updated: 2024/02/26 18:05:21 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void     remove_fd_nums(char *cmd_str, uint32_t idx_redir);
static void     remove_filename(char *cmd_str, uint32_t idx_redir);
static void     fill_redir_input(t_list **redirs, char *str, uint32_t i);
static void     fill_redir_heredoc(t_list **redirs, char *str, uint32_t i, int32_t heredoc_fileno);
static void     fill_redir_output(t_list **redirs, char *str, uint32_t i, bool is_append);
static int32_t  get_fd_num(char *str, uint32_t idx_redir, uint8_t before_after);
static char     *get_filename(char *str, uint32_t idx_redir);
static t_redir  *init_redir(void);

t_list  *fill_redirs(char *cmd_str)
{
    t_list          *redirs;
    uint32_t        i;
    static int32_t  heredoc_fileno = 0;

    if (!cmd_str)
        return (NULL);
    i = 0;
    redirs = NULL;
    while (cmd_str[i])
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
        i++;
    }
    return (heredoc_fileno++, lstreverse(&redirs), redirs);
}

void    clear_redirs(t_list *redirs, char *cmd_str)
{
    uint32_t    i;
    t_redir     *redir;

    if (!cmd_str || !redirs)
        return ;
    i = 0;
    while (cmd_str[i])
    {
        if (cmd_str[i] == '<' || cmd_str[i] == '>')
        {
            redir = (t_redir *)redirs->content;
            if (redir->fds[1] == -42)
                remove_filename(cmd_str, i);
            remove_fd_nums(cmd_str, i);
            cmd_str[i] = ' ';
            if (cmd_str[i + 1] == '<' || cmd_str[i + 1] == '>')
                cmd_str[++i] = ' ';
            redirs = redirs->next;
        }
        else if (is_shell_space(cmd_str[i])) //NON ELSE IF perche' remove filename incrementa la i uno di troppo
            cmd_str[i] = ' ';
        i++;
    }
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
    redir->fds[0] = get_fd_num(str, i, AFTER);
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
    redir->fds[1] = get_fd_num(str, i, AFTER);
    redir->fds[0] = get_fd_num(str, i, BEFORE);
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
	while (str[i] && is_shell_space(str[i]))
		i++;
	len = 0;
	while (str[i + len] && !is_shell_space(str[i + len]))
		len++;
	filename = calloc_p(len + 1, sizeof(char));
	ft_strlcpy(filename, &str[i], len + 1);
    restore_placeholders(filename, g_ph_redirl);
    restore_placeholders(filename, g_ph_redirr);
	return (filename);
}

static int32_t get_fd_num(char *str, uint32_t idx_redir, uint8_t direction)
{
    uint32_t    i;
    int32_t     num;

    num = -42;
    i = idx_redir + (direction == AFTER) - (direction == BEFORE);
    if (direction == AFTER)
    {
        if (str[i] == '&' && ft_isdigit(str[i + 1]))
            num = ft_atou(&str[i + 1]);
    }
    else
    {
        while (str[i] && ft_isdigit(str[i]))
            i--;
        if (is_shell_space(str[i]))
            num = ft_atou(&str[i + 1]);
    }
    return (num);
}

static void remove_fd_nums(char *cmd_str, uint32_t idx_redir)
{
    int32_t i;

    i = idx_redir + 1 + (cmd_str[idx_redir + 1] == '<' || cmd_str[idx_redir + 1] == '>');
    if (cmd_str[i] == '&')
        cmd_str[i++] = ' ';
    while (cmd_str[i] && ft_isdigit(cmd_str[i]))
        cmd_str[i++] = ' ';
    i = idx_redir - 1;
    while (i >= 0 && ft_isdigit(cmd_str[i]))
        cmd_str[i--] = ' ';
}

static void  remove_filename(char *cmd_str, uint32_t idx_redir)
{
    uint32_t   i;

    i = idx_redir + 1 + (cmd_str[idx_redir + 1] == '<' || cmd_str[idx_redir + 1] == '>');
    while (cmd_str[i] && is_shell_space(cmd_str[i]))
        cmd_str[i++] = ' ';
    while (cmd_str[i] && !is_shell_space(cmd_str[i]))
        cmd_str[i++] = ' ';
}