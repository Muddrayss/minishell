/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:45:10 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 16:05:33 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int8_t	check_tokens(const t_list *lexered_params);
static int8_t	check_parenthesis(const t_list *lexered_params);
static int8_t	check_quotes(const t_list *lexered_params);

int8_t	check_syntax(const t_list *const lexered_params)
{
	if (check_parenthesis(lexered_params) == -1)
		return (-1);
	if (check_tokens(lexered_params) == -1)
		return (-1);
	if (check_quotes(lexered_params) == -1)
		return (-1);
	if (check_redirs(lexered_params) == -1)
		return (-1);
	return (0);
}

static int8_t	check_parenthesis(const t_list *lexered_params)
{
	t_lexer	*elem;
	int16_t	n_open;

	n_open = 0;
	while (lexered_params)
	{
		elem = (t_lexer *)lexered_params->content;
		if (elem->token == SUBSHELL_START)
			n_open++;
		else if (elem->token == SUBSHELL_END)
		{
			n_open--;
			if (n_open < 0)
				return (tse(')'), -1);
		}
		lexered_params = lexered_params->next;
	}
	if (n_open)
		return (tse('('), -1);
	return (0);
}

static int8_t	check_tokens(const t_list *lexered_params)
{
	t_lexer		*elem;
	t_lexer		*ne;
	t_lexer		*pe;
	bool		in;
	bool		ip;

	while (lexered_params)
	{
		elem = (t_lexer *)lexered_params->content;
		ne = NULL;
		pe = NULL;
		if (lexered_params->next)
			ne = (t_lexer *)lexered_params->next->content;
		if (lexered_params->prev)
			pe = (t_lexer *)lexered_params->prev->content;
		if (elem->token && elem->token != 5 && elem->token != 6)
		{
			in = !ne || (!ne->cmd_str && ne->token != 5) || ne->token == 6;
			ip = !pe || (!pe->cmd_str && pe->token != 6) || pe->token == 5;
			if (in || ip)
				return (tse(g_parser_tokens[(int8_t)elem->token]), -1);
		}
		lexered_params = lexered_params->next;
	}
	return (0);
}

static int8_t	check_quotes(const t_list *lexered_params)
{
	char		master_quote;
	uint16_t	i;
	t_lexer		*elem;

	master_quote = '\0';
	while (lexered_params && master_quote == '\0')
	{
		elem = (t_lexer *)lexered_params->content;
		lexered_params = lexered_params->next;
		if (!elem->cmd_str)
			continue ;
		i = 0;
		while (elem->cmd_str[i])
		{
			if (!master_quote && is_quote(elem->cmd_str[i]))
				master_quote = elem->cmd_str[i];
			else if (elem->cmd_str[i] == master_quote)
				master_quote = '\0';
			i++;
		}
	}
	if (master_quote)
		return (tse(master_quote), -1);
	return (0);
}
