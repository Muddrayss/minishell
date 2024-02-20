/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:15:19 by egualand          #+#    #+#             */
/*   Updated: 2024/02/20 19:32:58 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	is_number(char *str);
static bool is_long_overflow(char *str);

void ft_exit(char **args)
{
	int8_t	id;

	if (!args[1])
	{
		free_data();
		exit(g_status);
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		free_data();
		exit(EXIT_FAILURE);
	}
	if (is_number(args[1]) && !is_long_overflow(args[1]))
	{
		id = ft_atou(args[1]);
		free_data();
		exit(id);
	}
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_data();
	exit(2);
}

static bool	is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == false)
			return (false);
		str++;
	}
	return (true);
}

static bool	is_long_overflow(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (ft_strcmp(str, "9223372036854775807") > 0)
		return (true);
	return (false);
}