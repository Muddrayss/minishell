/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:36:54 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:18:07 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	envp_matrix_remove(t_cc *const env_name, const uint16_t name_len)
{
	t_data		*data;
	char		**new_matrix;
	uint16_t	old_size;
	uint16_t	i;

	data = get_data();
	old_size = data->envp_size + 1;
	new_matrix = (char **)malloc_p(sizeof(char *) * old_size, PERM);
	new_matrix[old_size - 1] = NULL;
	i = old_size - 2;
	while (old_size--)
	{
		if (!ft_strncmp(data->envp_matrix[old_size], env_name, name_len) == 0)
			new_matrix[i--] = data->envp_matrix[old_size];
		else
			free(data->envp_matrix[old_size]);
	}
	free(data->envp_matrix);
	data->envp_matrix = new_matrix;
	return ;
}

void	envp_matrix_add(t_cc *str)
{
	t_data		*data;
	char		**new_matrix;
	uint16_t	size;

	data = get_data();
	size = data->envp_size;
	new_matrix = (char **)malloc_p(sizeof(char *) * (size + 1), PERM);
	new_matrix[size--] = NULL;
	new_matrix[size] = (char *)str;
	while (size--)
		new_matrix[size] = data->envp_matrix[size];
	free(data->envp_matrix);
	data->envp_matrix = new_matrix;
	return ;
}

void	envp_print_env(void)
{
	t_cc **const	matrix = (t_cc **)get_data()->envp_matrix;
	uint16_t		i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strchr(matrix[i], '='))
			printf("%s\n", matrix[i]);
		i++;
	}
}
