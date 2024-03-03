/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:36:54 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 18:45:28 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	envp_matrix_remove(const char *const env_name, const uint16_t name_len)
{
	uint16_t	old_size;
	uint16_t	i;
	char		**matrix;
	char		**new_matrix;
	t_data		*data;

	data = get_data();
	matrix = data->envp_matrix;
	old_size = data->envp_size + 1;
	new_matrix = (char **)malloc_p(sizeof(char *) * old_size); //+1 e -1
	new_matrix[old_size - 1] = NULL;
	i = old_size - 2;
	while (old_size--)
	{
		if (ft_strncmp(matrix[old_size], env_name, name_len) == 0)
			free_and_null((void **)&matrix[old_size]);
		else
			new_matrix[i--] = matrix[old_size];
	}
	free_and_null((void **)&matrix);
	data->envp_matrix = new_matrix;
	return ;
}

void	envp_matrix_add(const char *str)
{
	t_data		*data;
	char		**matrix;
	char		**new_matrix;
	uint16_t	size;

	data = get_data();
	matrix = data->envp_matrix;
	size = data->envp_size;
	new_matrix = (char **)malloc_p(sizeof(char *) * (size + 1));
	new_matrix[size--] = NULL;
	new_matrix[size] = (char *)str;
	while (size--)
		new_matrix[size] = matrix[size];
	data->envp_matrix = new_matrix;
	free_and_null((void **)&matrix); //non ft_freematrix
	return ;
}

void	envp_print_env(void)
{
	char		**matrix;
	uint16_t	i;

	matrix = get_data()->envp_matrix;
	i = 0;
	while (matrix[i])
	{
		if (ft_strchr(matrix[i], '='))
			printf("%s\n", matrix[i]);
		i++;
	}
}
