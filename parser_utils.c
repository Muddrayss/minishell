/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:45 by craimond          #+#    #+#             */
/*   Updated: 2024/01/29 22:15:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static unsigned int	get_x_between_pipes(t_list *lexered_params, uint8_t flag);

unsigned int	check_token_streak(t_token *next_token, t_list *lexered_params)
{
	unsigned int	token_streak;
	t_lexer			*elem;
	t_list			*tmp;

	token_streak = 0;
	tmp = lexered_params;
	while (tmp)
	{
		elem = (t_lexer *)tmp->content;
		if (elem->type == TOKEN)
			token_streak++;
		else
			break ;
		tmp = tmp->next;
	}
	if (next_token && token_streak > 1)
		*next_token = ((t_lexer *)lexered_params->next->content)->str.token;
	else if (next_token)
		*next_token = EMPTY;
	return (token_streak);
}

t_parser	*new_elem(size_t *size, t_list *lexered_params)
{
	t_parser		*elem;

	elem = (t_parser *)malloc(sizeof(t_parser));
	if (!elem)
		ft_quit(10, "failed to allocate memory");
	elem->redirs = NULL;
	elem->pid = -1;
	*size = get_x_between_pipes(lexered_params, CMD_LEN) + 2;
	elem->cmd_str = (char *)ft_calloc(*size, sizeof(char));
	if (!elem->cmd_str)
	{
		free(elem);
		ft_quit(12, "failed to allocate memory");
	}
	return (elem);
}

static unsigned int	get_x_between_pipes(t_list *node, uint8_t flag)
{
	unsigned int	n;
	t_lexer			l_content;

	n = 0;
	while (node)
	{
		l_content = *((t_lexer *)node->content);
		if (flag == CMD_LEN && l_content.type == CMD)
			n += ft_strlen(l_content.str.cmd) + 1; // per eventuali token
		else if (l_content.type == TOKEN && l_content.str.token == PIPE)
			break ;
		node = node->next;
	}
	return (n);
}

t_lexer	*get_next_cmd_elem(t_list *node)
{
	t_lexer	*elem;

	while (node)
	{
		elem = (t_lexer *)node->content;
		if (elem->type == CMD)
			return (elem);
		node = node->next;
	}
	return (NULL);
}

bool	is_empty_cmd(void *content)
{
	t_lexer	*elem;
	char	*tmp;

	elem = (t_lexer *)content;
	tmp = NULL;
	if (elem->type == CMD)
	{
		tmp = ft_strtrim(elem->str.cmd, " \t\n");
		if (!tmp)
			ft_quit(15, "failed to allocate memory");
		if (*tmp == '\0')
			return (free(tmp), true);
	}
	return (free(tmp), false);
}

void	del_content_parser(void *content)
{
	t_parser	*elem;

	elem = (t_parser *)content;
	free(elem->cmd_str);
	ft_lstclear(&elem->redirs, &del_content_redirs);
	free(elem);
}

void	del_content_redirs(void *content)
{
	t_redir *elem;

	elem = (t_redir *)content;
	if (elem->filename)
		free(elem->filename);
}