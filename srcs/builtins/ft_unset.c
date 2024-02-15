/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:42 by egualand          #+#    #+#             */
/*   Updated: 2024/02/13 18:24:43 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_unset(char **args)
{
	int		i;
	uint8_t	exit_status;

	i = 0;
	exit_status = EXIT_SUCCESS;
	while (args[++i])
	{
		if (ft_strchr(args[i], '=') == NULL)	
			ft_unsetenv(args[i]);
		else 
		{
			ft_putstr_fd("unset: not a valid identifier\n", STDERR_FILENO);
			exit_status = EXIT_FAILURE;
		}
	}
	exit(exit_status);
}