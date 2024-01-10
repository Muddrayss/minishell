/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/01/10 01:27:47 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(t_list *lexered_params, t_data *data)
{
	t_list			*parsed_params;
	t_parser		*content_par;
	t_lexer			*prev_cmd_elem;
	t_lexer			*content_lex;
	t_lexer			*next_cmd_elem;
	char			*cmd_str;
	size_t			size;

	content_par = new_elem(data);
	size = get_len(lexered_params);
	cmd_str = (char *)ft_calloc(size, sizeof(char));
	if (!cmd_str)
		ft_quit(11, "failed to allocate memory", data);
	while (lexered_params)
	{
		content_lex = (t_lexer *)lexered_params->content;
		if (content_lex->type == CMD)
		{
			ft_strlcat(cmd_str, content_lex->str.cmd, size);
			prev_cmd_elem = content_lex;
		}
		else if (content_lex->type == TOKEN)
		{
			next_cmd_elem = get_next_cmd_elem(lexered_params);
			if (content_lex->str.token == PIPE)
			{
				ft_lstadd_back(parsed_params, ft_lstnew(content_par));
				content_par = new_elem(data);
			}
			else if (content_lex->str.token == REDIR_L)
				handle_redir_l(prev_cmd_elem->str.cmd, next_cmd_elem->str.cmd, content_par, data);
		}
		lexered_params = lexered_params->next;
	}
	return (parsed_params);
}

static t_lexer	*get_next_cmd_elem(t_list *lexered_params)
{
	t_lexer			*content_lex;

	while (lexered_params)
	{
		content_lex = (t_lexer *)lexered_params->content;
		if (content_lex->type == CMD)
			return (content_lex);
		lexered_params = lexered_params->next;
	}
	return (NULL);
}

static void	handle_redir_l(char *prev_cmd,  char *next_cmd, t_parser *content_par, t_data *data)
{
	t_redir	*redir_content;

	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory", data);
	redir_content->fds[0] = -42;
	redir_content->fds[1] = STDIN_FILENO;
	add_left_right_fds(&redir_content->fds, prev_cmd, PREV, data);
	add_left_right_fds(&redir_content->fds, next_cmd, NEXT, data);
	content_par->redirections = NULL;
	ft_lstadd_front(&content_par->redirections, ft_lstnew(redir_content));
}

static void	add_left_right_fds(int *fds[], char *cmd, uint8_t flag, t_data *data)
{
	unsigned int	i;

	if (flag == PREV)
	{
		i = ft_strlen(cmd) - 1;
		while (cmd[i] && ft_isdigit(cmd[i]))
			i--;
	}
	else
	{
		i = 0;
		if (cmd[i] == '&')
			i++;
		while (cmd[i] && ft_isdigit(cmd[i]))
			i++;
	}
	if (is_shell_space(cmd[i]))
		(*fds)[flag] = ft_atoi(cmd + i * (flag == PREV));
}

static void	add_filename_fds(int *fds[], char *cmd, uint8_t flag, t_data *data)
{
	unsigned int	i;
	char			*tmp;
	char			*filename;

	if (flag == PREV)
	{
		i = ft_strlen(cmd) - 1;
		while (cmd[i] && is_shell_space(cmd[i]))
			i--;
		while (cmd[i] && !is_shell_space(cmd[i]))
			i--;
		tmp = ft_strdup(&cmd[i + 1]);
		if (!tmp)
			ft_quit(16, "failed to allocate memory", data);
		filename = ft_strtrim(tmp, " \n\t");
		free(tmp);
		if (!filename)
			ft_quit(16, "failed to allocate memory", data);
	}
	else if (flag == NEXT)
	{
		i = 0;
		while (cmd[i] && is_shell_space(cmd[i]))
			i++;
		filename = ft_strdup(&cmd[i]);
		if (!filename)
			ft_quit(16, "failed to allocate memory", data);
		while (cmd[i] && !is_shell_space(cmd[i]))
			i++;
		filename[i] = '\0';
	}
	(*fds)[flag] = open(filename, O_RDWR | O_CREAT);
	free(filename);
	if ((*fds)[flag] == -1)
		ft_putstr_fd("No such file or directory", 1);
}

static unsigned int	get_len(t_list *lexered_params)
{
	unsigned int	cmd_len;
	t_lexer			l_content;

	cmd_len = 0;
	l_content = *((t_lexer *)lexered_params->content);
	while (lexered_params)
	{
		l_content = *((t_lexer *)lexered_params->content);
		if (l_content.type == CMD)
			cmd_len += ft_strlen(l_content.str.cmd);
		lexered_params = lexered_params->next;
	}
}

static t_parser	*new_elem(t_data *data)
{
	t_parser *elem;

	elem = (t_parser *)malloc(sizeof(t_parser));
	if (!elem)
		ft_quit(10, "failed to allocate memory", data);
	elem->cmd_args = NULL;
	elem->redirections = NULL;
}