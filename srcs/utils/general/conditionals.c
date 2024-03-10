/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:12:51 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool	is_quote(t_cc c)
{
	return (c == '\'' || c == '\"');
}

bool	is_shell_space(t_cc c)
{
	return (ft_strchr(g_shell_spaces, c) != NULL);
}

bool	is_empty_str(t_cc *str)
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

bool	is_digit(t_cc c)
{
	return (c >= '0' && c <= '9');
}
