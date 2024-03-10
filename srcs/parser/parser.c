/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:19:32 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:12:01 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_parser	*init_cmd(t_cc type, t_cc *const cmd_str);
static t_tree	*fill_tree(const t_list *const lexered_params,
					const t_list *const stop);
static t_list	*skip_parenthesis(const t_list *lexered_params);
static t_list	*unskip_parenthesis(const t_list *lexered_params);

t_tree	*parser(t_list *lexered_params)
{
	lstremoveif(&lexered_params, &is_empty_cmd, NULL);
	if (merge_separators(&lexered_params) == -1
		|| check_syntax(lexered_params) == -1)
	{
		g_status = 2;
		return (NULL);
	}
	return (fill_tree(lexered_params, NULL));
}

static t_tree	*fill_tree(const t_list *const lp,
	const t_list *const stop)
{
	t_tree	*node;
	t_lexer	*elem;
	t_lexer	*next_elem;

	if (!lp)
		return (NULL);
	elem = (t_lexer *)lp->content;
	if (elem->token == SUBSHELL_START)
		return (fill_tree(skip_parenthesis(lp), stop));
	if (lp->next == stop)
	{
		node = treenew(init_cmd(END, NULL), TMP);
		if (elem->token == SUBSHELL_END)
			node = tb(node, fill_tree(unskip_parenthesis(lp), lp));
		else
			node = tb(node, treenew(init_cmd(elem->token, elem->cmd_str), TMP));
		return (node);
	}
	next_elem = (t_lexer *)lp->next->content;
	node = treenew(init_cmd(next_elem->token, next_elem->cmd_str), TMP);
	if (elem->token != SUBSHELL_END)
		node = tb(node, treenew(init_cmd(elem->token, elem->cmd_str), TMP));
	else
		node = tb(node, fill_tree(unskip_parenthesis(lp), lp));
	return (node = tb(node, fill_tree(lp->next->next, stop)), node);
}

static t_list	*skip_parenthesis(const t_list *lexered_params)
{
	t_lexer		*elem;
	uint16_t	n_open;

	n_open = 1;
	while (n_open && lexered_params->next)
	{
		lexered_params = lexered_params->next;
		elem = (t_lexer *)lexered_params->content;
		if (elem->token == SUBSHELL_END)
			n_open--;
		else if (elem->token == SUBSHELL_START)
			n_open++;
	}
	return ((t_list *)lexered_params);
}

static t_list	*unskip_parenthesis(const t_list *lexered_params)
{
	t_lexer		*elem;
	uint16_t	n_close;

	n_close = 1;
	while (n_close && lexered_params->prev)
	{
		lexered_params = lexered_params->prev;
		elem = (t_lexer *)lexered_params->content;
		if (elem->token == SUBSHELL_END)
			n_close++;
		else if (elem->token == SUBSHELL_START)
			n_close--;
	}
	return (lexered_params->next);
}

static t_parser	*init_cmd(t_cc type, t_cc *const cmd_str)
{
	t_parser	*node;

	node = (t_parser *)malloc_p(sizeof(t_parser), TMP);
	node->type = type;
	node->cmd = NULL;
	if (cmd_str)
	{
		node->cmd = (t_cmd *)malloc_p(sizeof(t_cmd), TMP);
		node->cmd->redirs = fill_redirs(cmd_str);
		node->cmd->cmd_str = clear_redirs(cmd_str);
	}
	return (node);
}
