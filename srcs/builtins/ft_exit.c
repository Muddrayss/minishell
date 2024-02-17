/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:15:19 by egualand          #+#    #+#             */
/*   Updated: 2024/02/17 15:18:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	is_number(char *str);

void ft_exit(char **args)
{
	if (!args[1])
		exit(EXIT_SUCCESS);
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (is_number(args[1]))
		exit((uint8_t)ft_atou(args[1])); //non basta atoi, va paddato in un range (overflow underflow)
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(2); //nel mio bash da casa è 2, non 255
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
