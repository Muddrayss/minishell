/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:27:44 by egualand          #+#    #+#             */
/*   Updated: 2024/02/13 18:24:35 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_export(char **args)
{
	int	i;
	char *key;
	char *env_var;
	
	i = 0;
	while (args[++i])
	{
		key = ft_strchr(args[i], '=');
		env_var = ft_getenv(args[i]);
		if (env_var)
		{
			ft_setenv(args[i], key + 1, true);
			free(env_var);
		}
		else
			ft_setenv(args[i], key + 1, false);
	}
	g_status = EXIT_SUCCESS;
}
