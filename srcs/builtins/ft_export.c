/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:27:44 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export(t_cc *const *args)
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
			env_name = (char *)malloc_p(sizeof(char) * (sep - *args + 2), TMP);
			ft_strlcpy(env_name, *args, sep - *args + 2);
			env_value = ft_strdup(sep + 1, TMP);
		}
		else
		{
			env_name = ft_strjoin(*args, "=", TMP);
			env_value = "";
		}
		ft_setenv(env_name, env_value, true);
	}
}
