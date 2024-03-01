/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:36:54 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 16:09:51 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	envp_matrix_remove(char *env_name, uint32_t name_len)
{
	uint16_t	size;
	uint16_t	i;
	char		**matrix;
	char		**new_matrix;

	matrix = get_data()->envp_matrix;
	size = ft_matrixsize(matrix);
	new_matrix = malloc_p(sizeof(char *) * size);
	new_matrix[size - 1] = NULL;
	i = size - 1;
	while (size--)
	{
		if (ft_strncmp(matrix[size], env_name, name_len) == 0)
			free(matrix[size]);
		else
			new_matrix[i--] = matrix[size];
	}
	free(matrix);
	return ;
}

void	envp_matrix_add(char *str)
{
	char		**matrix;
	char		**new_matrix;
	uint32_t	size;

	matrix = get_data()->envp_matrix;
	size = ft_matrixsize(matrix);
	new_matrix = malloc_p(sizeof(char *) * (size + 2));
	new_matrix[size - 1] = NULL;
	new_matrix[size] = str;
	while (size--)
		new_matrix[size] = matrix[size];
	get_data()->envp_matrix = new_matrix;
	free(matrix); //non ft_freematrix
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
