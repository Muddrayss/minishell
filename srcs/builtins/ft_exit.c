/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:15:19 by egualand          #+#    #+#             */
/*   Updated: 2024/02/18 16:18:52 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	is_number(char *str);
static bool is_long_type_overflow(char *str);

void ft_exit(char **args)
{
	dprintf(2, "exit deb\n");
	if (!args[1])
		exit(g_status);
	dprintf(2, "exit deb2\n");
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	dprintf(2, "exit deb3\n");
	if (is_number(args[1]) && !is_long_type_overflow(args[1]))
		exit((uint8_t)ft_atou(args[1]));
	dprintf(2, "exit deb4\n");
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
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

static bool	is_long_type_overflow(char *str)
{
	if (*str == '-' || *str == '+')
	{
		str++;
		if (ft_strcmp(str, "9223372036854775808") > 0)
			return (true);
	}
	else
	{
		if (ft_strcmp(str, "9223372036854775807") > 0)
			return (true);
	}
	return (false);
}