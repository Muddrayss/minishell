/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:15:19 by egualand          #+#    #+#             */
/*   Updated: 2024/02/13 18:24:31 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_exit(char **args)
{
	int 	i;
	uint8_t exit_status;

	i = 0;
	exit_status = EXIT_SUCCESS;
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			exit_status = EXIT_FAILURE;
		}
		else
		{
			if (ft_isnumber(args[1]))
				exit_status = ft_atou(args[1]); //non basta atoi, va paddato in un range (overflow underflow)
			else
			{
				ft_putstr_fd("exit: ", STDERR_FILENO);
				ft_putstr_fd(args[1], STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				exit_status = 2; //nel mio bash da casa è 2, non 255
			}
		}
	}
	exit(exit_status);
}