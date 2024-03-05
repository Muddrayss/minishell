/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:29:39 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 08:36:36 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_env(const char *const *args)
{
	g_status = EXIT_SUCCESS;
	if (args[1])
	{
		g_status = EXIT_FAILURE;
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return ;
	}
	envp_print_env();
}