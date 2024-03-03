/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:42 by egualand          #+#    #+#             */
/*   Updated: 2024/03/03 14:32:06 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_unset(char **args)
{
	char	*name;
	uint8_t	exit_status;

	exit_status = EXIT_SUCCESS;
	while (*(++args))
	{
		if (!ft_strchr(*args, '='))
		{
			name = strjoin_p(*args, "=");
			ft_unsetenv(name);
			free_and_null((void **)&name);
		}
		else 
		{
			ft_putstr_fd("unset: not a valid identifier\n", STDERR_FILENO);
			exit_status = EXIT_FAILURE;
		}
	}
	g_status = exit_status;
}