/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:24:52 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool	is_empty_cmd(const void *const content)
{
	const t_lexer *const	elem = (t_lexer *)content;

	if (elem->token == 0 && is_empty_str(elem->cmd_str))
		return (true);
	return (false);
}

bool	is_redir(t_cc c)
{
	return (c == '<' || c == '>');
}
