/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:27:44 by egualand          #+#    #+#             */
/*   Updated: 2024/03/01 16:36:08 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export(char **args)
{
	char	*env_name;
	char	*env_value;
	char	*sep;
	
	if (!args[1])
	{
		envp_print_export(get_data()->envp_tree);
		g_status = EXIT_SUCCESS;
		return ;
	}
	while (*args)
	{
		sep = ft_strchr(*args, '=');
		if (sep)
		{
			env_name = (char *)malloc(sep - *args + 1);
			ft_strlcpy(env_name, *args, sep - *args + 1);
			env_value = ft_strdup(sep + 1);
		}
		else
		{
			env_name = ft_strdup(*args);
			env_value = ft_strdup("");
		}
		if (!env_name || !env_value)
			ft_quit(ERR_MEM, "minishell: failed to allocate memory");
		ft_setenv(env_name, env_value, true);
		free(env_name);
		free(env_value);
		args++;
	}
	g_status = EXIT_SUCCESS;
}
