/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:59:34 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:08:41 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void		merge_pipes(t_list **const head, t_list **const node);
static int8_t	merge_ampersands(t_list **const head, t_list **const node);

int8_t	merge_separators(t_list **const lexered_params)
{
	t_list	*node;
	t_lexer	*elem;
	int8_t	ret;

	ret = 0;
	node = (t_list *)*lexered_params;
	while (node && ret == 0)
	{
		elem = (t_lexer *)node->content;
		if (elem->token)
		{
			if (elem->token == '|')
				merge_pipes(lexered_params, &node);
			else if (elem->token == '&')
				ret = merge_ampersands(lexered_params, &node);
			else if (elem->token == '(')
				elem->token = SUBSHELL_START;
			else
				elem->token = 1 * (elem->token == ';')
					+ 6 * (elem->token == ')');
		}
		if (node)
			node = node->next;
	}
	return (ret);
}

static int8_t	merge_ampersands(t_list **const head, t_list **const node)
{
	t_lexer	*elem;
	t_lexer	*next_elem;

	elem = (t_lexer *)(*node)->content;
	next_elem = NULL;
	if ((*node)->next)
		next_elem = (t_lexer *)(*node)->next->content;
	if (next_elem && next_elem->token == '&')
	{
		elem->token = AND;
		lstremoveone(head, (*node)->next, NULL);
	}
	else
		return (tse('&'), -1);
	return (0);
}

static void	merge_pipes(t_list **const head, t_list **const node)
{
	t_lexer	*elem;
	t_lexer	*next_elem;
	t_list	*node_prev;

	next_elem = NULL;
	elem = (t_lexer *)(*node)->content;
	if ((*node)->next)
		next_elem = (t_lexer *)(*node)->next->content;
	if (next_elem && next_elem->token == '|')
	{
		elem->token = OR;
		node_prev = (*node)->prev;
		lstremoveone(head, (*node)->next, NULL);
		*node = node_prev;
	}
	else
		elem->token = PIPELINE;
}
