/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:19:32 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 23:00:16 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_parser	*init_cmd(const char type, const char *const cmd_str);
static t_tree	*fill_tree(const t_list *const lexered_params, const t_list *const stop);
static t_list	*skip_parenthesis(const t_list *lexered_params);
static t_list	*unskip_parenthesis(const t_list *lexered_params);

t_tree	*parser(t_list *lexered_params)
{
	lstremoveif(&lexered_params, &is_empty_cmd);
	if (merge_separators(&lexered_params) == -1 || check_syntax(lexered_params) == -1)
	{
		g_status = 2;
		return (NULL);
	}
	return(fill_tree(lexered_params, NULL));
}

static t_tree	*fill_tree(const t_list *const lexered_params, const t_list *const stop)
{
	t_tree	*node;
	t_lexer	*elem;
	t_lexer	*next_elem;

	if (!lexered_params)
		return (NULL);
	elem = (t_lexer *)lexered_params->content;
	if (elem->token == SUBSHELL_START)
		return (fill_tree(skip_parenthesis(lexered_params), stop));
	if (lexered_params->next == stop)
	{
		node = treenew_p(init_cmd(END, NULL));
		if (elem->token == SUBSHELL_END)
			node = treeadd_below(node, fill_tree(unskip_parenthesis(lexered_params), lexered_params));
		else
			node = treeadd_below(node, treenew_p(init_cmd(elem->token, elem->cmd_str)));
		return (node);
	}
	next_elem = (t_lexer *)lexered_params->next->content;
	node = treenew_p(init_cmd(next_elem->token, next_elem->cmd_str));
	if (elem->token != SUBSHELL_END)
		node = treeadd_below(node, treenew_p(init_cmd(elem->token, elem->cmd_str)));
	else
		node = treeadd_below(node, fill_tree(unskip_parenthesis(lexered_params), lexered_params));
	node = treeadd_below(node, fill_tree(lexered_params->next->next, stop));
	return (node);
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

static t_parser	*init_cmd(const char type, const char *const cmd_str)
{
	t_parser	*node;

	node = (t_parser *)malloc_p(sizeof(t_parser));
	node->type = type;
	node->cmd = NULL;
	if (cmd_str)
	{
		node->cmd = (t_cmd *)malloc_p(sizeof(t_cmd));
		node->cmd->redirs = fill_redirs(cmd_str);
		node->cmd->cmd_str = clear_redirs(cmd_str);
	}
	return (node);
}
