/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:15:19 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 08:31:30 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	is_number(const char *str);
static bool is_long_overflow(const char *str);

void ft_exit(const char *const *args)
{
	uint8_t	id;

	if (!args[1])
		id = g_status;
	else if (args[2])
	{
		id = EXIT_FAILURE;
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	}
	if (is_number(args[1]) && !is_long_overflow(args[1]))
		id = (uint8_t)ft_atoi(args[1]);
	else
	{
		id = 2;
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	free_data();
	exit(id);
}

static bool	is_number(const char *str)
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

static bool	is_long_overflow(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (ft_strcmp(str, "9223372036854775807") > 0)
		return (true);
	return (false);
}