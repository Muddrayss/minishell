/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:27:44 by egualand          #+#    #+#             */
/*   Updated: 2024/02/21 15:44:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export(char **args)
{
	int		i;
	char 	*sep;
	
	if (!args[1])
	{
		envp_matrix_print(true);
		g_status = EXIT_SUCCESS;
		return ;
	}
	i = 0;
	while (args[++i])
	{
		sep = ft_strchr(args[i], '=');
		if (!sep)
			ft_setenv(args[i], "", true);
		else
		{
			*sep = '\0';
			ft_setenv(args[i], sep + 1, true);
		}
	}
	g_status = EXIT_SUCCESS;
}
