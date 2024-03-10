/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:46:00 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:19:10 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	envp_init(t_cc **const envp)
{
	t_data		*data;
	char		*str;
	uint16_t	size;

	data = get_data();
	size = ft_matrixsize(envp);
	data->envp_size = size;
	data->envp_tree = NULL;
	data->envp_matrix = (char **)malloc_p(sizeof(char *) * (size + 1), PERM);
	data->envp_matrix[size] = NULL;
	while (size--)
	{
		str = ft_strdup(envp[size], PERM);
		data->envp_tree = envp_tree_add(data->envp_tree, str);
		data->envp_matrix[size] = str;
	}
}

void	ft_setenv(t_cc *const name, t_cc *const val, const bool rep)
{
	t_data				*data;
	t_cc *const			str = ft_strjoin(name, val, PERM);

	data = get_data();
	if (rep && ft_getenv(name))
		ft_unsetenv(name);
	data->envp_size++;
	data->envp_tree = envp_tree_add(data->envp_tree, str);
	envp_matrix_add(str);
}

void	ft_unsetenv(t_cc *const name)
{
	t_data		*data;
	uint16_t	name_len;

	if (!ft_getenv(name))
		return ;
	name_len = ft_strlen(name);
	data = get_data();
	data->envp_size--;
	data->envp_tree = envp_tree_remove(data->envp_tree, name, name_len);
	envp_matrix_remove(name, name_len);
}

char	*ft_getenv(t_cc *const name)
{
	char				*value;
	const t_tree *const	found
		= envp_tree_find(get_data()->envp_tree, name, ft_strlen(name));

	if (found)
	{
		value = ft_strchr((char *)found->content, '=');
		if (value)
			return (value + 1);
		else
			return (NULL);
	}
	return (NULL);
}
