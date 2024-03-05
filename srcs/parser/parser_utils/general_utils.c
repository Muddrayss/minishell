/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:24:52 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 21:49:42 by craimond         ###   ########.fr       */
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

bool	is_redir(const char c)
{
	return (c == '<' || c == '>');
}
