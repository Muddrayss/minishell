/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:29:39 by egualand          #+#    #+#             */
/*   Updated: 2024/02/13 18:24:28 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_env(char **args)
{
	int	i;

	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		g_status = EXIT_FAILURE;
	}
	else
		print_envp_table();
	g_status = EXIT_SUCCESS;
}