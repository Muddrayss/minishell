/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:42 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 21:36:48 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_unset(const char *const *args)
{
	char	*name;

	g_status = EXIT_SUCCESS;
	while (*(++args))
	{
		if (!ft_strchr(*args, '='))
		{
			name = strjoin_p(*args, "=");
			ft_unsetenv(name);
		}
		else
		{
			g_status = EXIT_FAILURE;
			ft_putstr_fd("unset: not a valid identifier\n", STDERR_FILENO);
		}
	}
}
