/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:58:14 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:13 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static uint16_t	skip_flags(t_cc *const *args, bool *is_n);

void	ft_echo(t_cc *const *args)
{
	uint16_t	i;
	bool		is_n;

	i = skip_flags(args, &is_n);
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_status = EXIT_SUCCESS;
}

static uint16_t	skip_flags(t_cc *const *args, bool *is_n)
{
	uint16_t	i;
	uint16_t	j;

	*is_n = false;
	i = 0;
	if (!args[1] || args[1][0] != '-')
		return (1);
	while (args[++i])
	{
		if (args[i][0] == '-')
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			*is_n = true;
		}
		else
			break ;
	}
	return (i);
}
