/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:36:54 by craimond          #+#    #+#             */
/*   Updated: 2024/02/19 15:49:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	update_env_matrix(t_envp elem, int8_t remove_add_replace) //se l'elemento da aggiungere o da rimuovere o  da rimpiazare
{
	char		**matrix;
	uint32_t	name_len;
	uint32_t    value_len;

	matrix = get_data()->envp_matrix;
	name_len = ft_strlen(elem.name);
	value_len = ft_strlen(elem.value);
	if (remove_add_replace == REMOVE)
		get_data()->envp_matrix = env_matrix_remove(matrix, elem.name, name_len);
	else if (remove_add_replace == ADD)
		get_data()->envp_matrix = env_matrix_add(matrix, elem, name_len, value_len);
	else if (remove_add_replace == REPLACE)
		get_data()->envp_matrix = env_matrix_replace(matrix, elem, name_len, value_len);
	free(matrix); //non ft_freematrix perche' altrimenti liberi anche i singoli elementi che sono stati spostati nella nuova matrice
}

char	**env_matrix_remove(char **matrix, char *env_name, uint32_t name_len)
{
	char		**new_matrix;
	uint32_t	i;
    size_t      size;

	size = ft_matrixsize(matrix) + 0;
	new_matrix = malloc_p(sizeof(char *) * size);
	new_matrix[size] = NULL;
	i = 0;
	while (matrix[++i])
	{
		if (ft_strncmp(matrix[i], env_name, name_len + 1) != 0)
			new_matrix[i] = matrix[i];
		else
			free(matrix[i]);
		i++;
	}
	return (new_matrix);
}

char	**env_matrix_replace(char **matrix, t_envp elem, uint32_t name_len, uint32_t value_len)
{
	char		**new_matrix;
	uint32_t	i;
    size_t      size;

	size = ft_matrixsize(matrix) + 1;
	new_matrix = malloc_p(sizeof(char *) * size);
	new_matrix[size - 1] = NULL;
	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], elem.name, name_len + 1) == 0)
		{
			new_matrix[i] = (char *)malloc(sizeof(char) * name_len + value_len + 2); //NON protected altrimenti non facciamo il free della matrice
			if (!new_matrix[i])
				return (ft_freematrix(new_matrix), ft_quit(ERR_MEM, "failed to allocate memory"), NULL);
			ft_strcpy(new_matrix[i], elem.name);
			new_matrix[i][name_len] = '=';
			ft_strcat(new_matrix[i], elem.value);
			free(matrix[i]);
		}
		else
			new_matrix[i] = matrix[i];
		i++;
	}
	return (new_matrix);
}

char	**env_matrix_add(char **matrix, t_envp  elem, uint32_t name_len, uint32_t value_len)
{
	char		**new_matrix;
	uint32_t	i;
    size_t      size;

	size = ft_matrixsize(matrix) + 2;
	new_matrix = malloc_p(sizeof(char *) * size);
	new_matrix[size - 1] = NULL;
	i = 0;
	while (matrix[i])
	{
		new_matrix[i] = matrix[i];
		i++;
	}
	new_matrix[i] = ft_calloc(name_len + value_len + 2, sizeof(char)); //NON protected altrimenti non facciamo il free della matrice
	if (!new_matrix[i])
		return (ft_freematrix(new_matrix), ft_quit(ERR_MEM, "failed to allocate memory"), NULL);
	ft_strcpy(new_matrix[i], elem.name);
	new_matrix[i][name_len] = '=';
	ft_strcat(new_matrix[i], elem.value);
	return (new_matrix);
}
