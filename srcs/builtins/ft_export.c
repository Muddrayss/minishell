/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:27:44 by egualand          #+#    #+#             */
/*   Updated: 2024/02/18 22:22:31 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//TODO gestire export senza opzioni (basta fare un muro di printf)
void	ft_export(char **args)
{
	int		i;
	char 	*sep;
	
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
