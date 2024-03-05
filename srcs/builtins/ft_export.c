/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:27:44 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 21:35:59 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export(const char *const *args)
{
	char	*env_name;
	char	*env_value;
	char	*sep;

	g_status = EXIT_SUCCESS;
	if (!args[1])
		envp_print_export(get_data()->envp_tree);
	while (*(++args))
	{
		sep = ft_strchr(*args, '=');
		if (sep)
		{
			env_name = (char *)malloc(sizeof(char) * (sep - *args + 2));
			ft_strlcpy(env_name, *args, sep - *args + 2);
			env_value = strdup_p(sep + 1);
		}
		else
		{
			env_name = strjoin_p(*args, "=");
			env_value = strdup_p("");
		}
		ft_setenv(env_name, env_value, true);
	}
}
