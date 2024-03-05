/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:12:51 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 17:20:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool	is_quote(const char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_shell_space(const char c)
{
	return (ft_strchr(g_shell_spaces, c) != NULL);
}

bool	is_empty_str(const char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!ft_strchr(g_shell_spaces, *str))
			return (false);
		str++;
	}
	return (true);
}

bool	is_bad_errno(const int erno)
{
	return (get_errnos()[erno]);
}

bool	is_digit(const char c)
{
	return (c >= '0' && c <= '9');
}
