/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:29:39 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:13 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_env(t_cc *const *args)
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
