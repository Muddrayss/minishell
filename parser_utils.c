/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:45 by craimond          #+#    #+#             */
/*   Updated: 2024/01/31 21:13:22 by craimond         ###   ########.fr       */
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
		if (elem->token)
			token_streak++;
		else
			break ;
		tmp = tmp->next;
	}
	if (next_token && token_streak > 1)
		*next_token = ((t_lexer *)lexered_params->next->content)->token;
	else if (next_token)
		*next_token = 0;
	return (token_streak);
}

t_parser	*new_elem(t_list *lexered_params)
{
	t_parser		*elem;
	unsigned int	size;

	elem = (t_parser *)malloc(sizeof(t_parser));
	if (!elem)
		ft_quit(10, "failed to allocate memory");
	elem->redirs = NULL;
	elem->pid = -1;
	size = get_x_between_pipes(lexered_params, CMD_LEN) + 2;
	elem->cmd_str = (char *)ft_calloc(size, sizeof(char));
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
	t_lexer			*l_content;
	t_lexer 		*l_content_next;

	n = 0;
	while (node)
	{
		l_content = (t_lexer *)node->content;
		if (node->next)
			l_content_next = (t_lexer *)node->next->content;
		else
			l_content_next = NULL;
		if (flag == CMD_LEN && l_content->cmd)
			n += ft_strlen(l_content->cmd) + 1;   // per eventuali token
		else if ((l_content->token && l_content->token == PIPE)
				&& l_content_next
				&& (l_content_next->token && l_content_next->token == PIPE))
			node = node->next;
		else if (l_content->token && l_content->token == PIPE)
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
		if (elem->cmd)
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
	if (elem->cmd)
	{
		tmp = ft_strtrim(elem->cmd, " \t\n");
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
}

void	del_content_redirs(void *content)
{
	t_redir *elem;

	elem = (t_redir *)content;
	if (elem->filename)
		free(elem->filename);
}