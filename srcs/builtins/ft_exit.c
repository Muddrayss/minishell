/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:15:19 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	is_number(t_cc *str);
static bool	is_long_overflow(t_cc *str);

void	ft_exit(t_cc *const *args)
{
	uint8_t	id;

	if (!args[1])
		id = g_status;
	else if (args[2])
	{
		id = EXIT_FAILURE;
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	}
	else
	{
		if (is_number(args[1]) && !is_long_overflow(args[1]))
			id = (uint8_t)ft_atoi(args[1]);
		else
		{
			id = 2;
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		}
	}
	release_resources();
	exit(id);
}

static bool	is_number(t_cc *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (is_digit(*str) == false)
			return (false);
		str++;
	}
	return (true);
}

static bool	is_long_overflow(t_cc *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (ft_strcmp(str, "9223372036854775807") > 0)
		return (true);
	return (false);
}
