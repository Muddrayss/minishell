/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:46:00 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 17:35:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	envp_init(const char **const envp)
{
	t_data		*data;
	char		**matrix;
	t_tree		*tree;
	char		*str;
	uint16_t	size;

	data = get_data();
	tree = NULL;
	size = ft_matrixsize(envp);
	data->envp_size = size;
	matrix = (char **)malloc_p(sizeof(char *) * (size + 1));
	matrix[size] = NULL;
	while (size--)
	{
		str = strdup_p(envp[size]);
		tree = envp_tree_add(tree, str);
		matrix[size] = str;
	}
	data->envp_tree = tree;
	data->envp_matrix = matrix;
}

void	ft_setenv(const char *const name, const char *const value, const bool replace)
{
	t_data				*data;
	const char *const	str = strjoin_p(name, value);

	data = get_data();
	if (replace && ft_getenv(name))
		ft_unsetenv(name);
	data->envp_size++;
	data->envp_tree = envp_tree_add(data->envp_tree, str);
	envp_matrix_add(str);
}

void	ft_unsetenv(const char *const name)
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

char	*ft_getenv(const char *const name)
{
	char				*value;
	const t_tree *const	found = envp_tree_find(get_data()->envp_tree, name, ft_strlen(name));

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
