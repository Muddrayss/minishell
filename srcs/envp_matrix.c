/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:36:54 by craimond          #+#    #+#             */
/*   Updated: 2024/02/21 16:04:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static char	*get_next_alphabetically(char **matrix, uint32_t size);

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
				return (ft_freematrix(new_matrix), ft_quit(ERR_MEM, "Error: failed to allocate memory"), NULL);
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
		return (ft_freematrix(new_matrix), ft_quit(ERR_MEM, "Error: failed to allocate memory"), NULL);
	ft_strcpy(new_matrix[i], elem.name);
	new_matrix[i][name_len] = '=';
	ft_strcat(new_matrix[i], elem.value);
	return (new_matrix);
}

//TODO handle cases where there is '=' in the value
//for some reason our export (or env) command adds extra " to the value
void	envp_matrix_print(bool is_export)
{
	uint8_t		i;
	char		**matrix;
	char		*to_print;
	uint32_t	size;
	uint32_t	name_len;

	matrix = get_data()->envp_matrix;
	if (is_export == false)
	{
		i = -1;
		while (matrix[++i])
			if (*(ft_strchr(matrix[i], '=') + 1))
				printf("%s\n", matrix[i]);
	}
	else
	{
		matrix = ft_strarrdup(get_data()->envp_matrix);
		if (!matrix)
			ft_quit(ERR_MEM, "Error: failed to allocate memory");
		size = ft_matrixsize(matrix);
		to_print = get_next_alphabetically(matrix, size);
		while (to_print)
		{
			write(STDOUT_FILENO, "declare -x ", 11);
			if (!ft_strchr(to_print, '='))
				name_len = ft_strlen(to_print);
			else
				name_len = ft_strchr(to_print, '=') - to_print;
			write(STDOUT_FILENO, to_print, name_len);
			write(STDOUT_FILENO, "=\"", 2);
			ft_putstr_fd(to_print + name_len + 1, STDOUT_FILENO);
			write(STDOUT_FILENO, "\"\n", 2);
			free(to_print);
			to_print = get_next_alphabetically(matrix, size);
		}
		free(matrix);
	}
}

static char	*get_next_alphabetically(char **matrix, uint32_t size)
{
	uint32_t	i;
	char		**first;
	char		*tmp;

	i = 0;
	first = NULL;
	while (i < size)
	{
		if (!first || !*first || (matrix[i] && ft_strcmp(matrix[i], *first) < 0))
			first = &matrix[i];
		i++;
	}
	tmp = ft_strdup(*first);
	free(*first);
	*first = NULL;
	return (tmp);
}
