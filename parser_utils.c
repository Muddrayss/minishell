/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:45 by craimond          #+#    #+#             */
/*   Updated: 2024/01/10 14:32:51 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	check_token_streak(t_token *next_token, t_list *lexered_params)
{
	unsigned int	token_streak;
	t_list			*tmp;

	token_streak = 0;
	tmp = lexered_params;
	while (((t_lexer *)tmp->content)->type == TOKEN && ((t_lexer *)tmp->content)->str.token != PIPE)
	{
		token_streak++;
		tmp = tmp->next;
	}
	*next_token = ((t_lexer *)lexered_params->next->content)->str.token;
	return (token_streak);
}

t_parser	*new_elem(t_data *data)
{
	t_parser *elem;

	elem = (t_parser *)malloc(sizeof(t_parser));
	if (!elem)
		ft_quit(10, "failed to allocate memory", data);
	elem->cmd_str = NULL;
	elem->redirections = NULL;
}

unsigned int	get_len_between_pipes(t_list *lexered_params)
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