/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:12:51 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 17:34:53 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

bool is_quote(const char c)
{
    return (c == '\'' || c == '\"');
}

bool is_redir(const char c)
{
	return (c == '<' || c == '>');
}

bool is_token(const char c)
{
	return (ft_strchr(g_tokens, c) != NULL);
}

bool is_shell_space(const char c)
{
    static char 	shell_spaces[] = {' ', '\n', '\t'};

    return (ft_strchr(shell_spaces, c) != NULL);
}

bool is_empty_str(const char *str)
{
	while (*str)
	{
		if (!is_shell_space(*str))
			return (false);
		str++;
	}
	return (true);
}

