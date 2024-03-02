/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:36:54 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 00:33:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	envp_matrix_remove(char *env_name, uint32_t name_len)
{
	uint16_t	old_size;
	uint16_t	i;
	char		**matrix;
	char		**new_matrix;
	t_data		*data;

	data = get_data();
	matrix = data->envp_matrix;
	old_size = data->envp_size + 1;
	new_matrix = (char **)malloc_p(sizeof(char *) * (old_size + 1 - 1)); //+1 e -1
	new_matrix[old_size - 1] = NULL;
	i = old_size - 2;
	while (old_size--)
	{
		if (ft_strncmp(matrix[old_size], env_name, name_len) == 0)
			ft_freenull((void **)&matrix[old_size]);
		else
			new_matrix[i--] = matrix[old_size];
	}
	ft_freenull((void **)&matrix);
	data->envp_matrix = new_matrix;
	return ;
}

void	envp_matrix_add(char *str)
{
	char		**matrix;
	char		**new_matrix;
	uint32_t	size;
	t_data		*data;

	data = get_data();
	matrix = data->envp_matrix;
	size = data->envp_size;
	new_matrix = (char **)malloc_p(sizeof(char *) * (size + 1));
	new_matrix[size--] = NULL;
	new_matrix[size] = str;
	while (size--)
		new_matrix[size] = matrix[size];
	data->envp_matrix = new_matrix;
	ft_freenull((void **)&matrix); //non ft_freematrix
	return ;
}

//TODO handle cases where there is '=' in the value
//for some reason our export (or env) command adds extra " to the value
void	envp_print_env(void)
{
	uint8_t		i;
	char		**matrix;

	matrix = get_data()->envp_matrix;
	i = -1;
	while (matrix[++i])
		if (*(ft_strchr(matrix[i], '=') + 1))
			printf("%s\n", matrix[i]);
}
