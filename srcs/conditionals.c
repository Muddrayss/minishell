/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:12:51 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 14:38:31 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

bool is_quote(char c)
{
    return (c == '\'' || c == '\"');
}

bool is_redir(char c)
{
	return (c == '<' || c == '>');
}

bool is_token(char c)
{
    uint8_t			        i;
	static const uint8_t	n_tokens = sizeof(g_tokens) / sizeof(g_tokens[0]);

	i = 0;
   	while (i < n_tokens)
		if (g_tokens[i++] == c)
			return (true);
	return (false);
}

bool is_shell_space(char c)
{
    uint8_t			i;
    static char 	shell_spaces[] = {' ', '\n', '\t'};
    static uint8_t	n_spaces = sizeof(shell_spaces) / sizeof(shell_spaces[0]);

    i = 0;
    while (i < n_spaces)
        if (c == shell_spaces[i++])
            return (true);
    return (false);
}

bool is_empty_str(char *str)
{
	while (*str)
	{
		if (!is_shell_space(*str))
			return (false);
		str++;
	}
	return (true);
}

