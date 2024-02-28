/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:36:54 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 00:23:27 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static char	*get_next_alphabetically(char **matrix, uint32_t size);

void	update_envp_matrix(t_envp elem, int8_t operation) //se l'elemento da aggiungere o da rimuovere o  da rimpiazare
{
	uint32_t	name_len;
	uint32_t    value_len;
	char		**matrix;

	matrix = get_data()->envp_matrix;
	name_len = ft_strlen(elem.name);
	value_len = ft_strlen(elem.value);
	if (operation == ADD)
		envp_matrix_add(matrix, elem, name_len, value_len);
	else if (operation == REMOVE)
		envp_matrix_remove(matrix, elem.name, name_len);
	else if (operation == REPLACE)
		envp_matrix_replace(matrix, elem, name_len, value_len);
}

void	envp_matrix_remove(char **matrix, char *env_name, uint32_t name_len)
{
	char		**new_matrix;
	uint32_t	i;
	uint32_t	j;
    size_t      size;
	char        *env_name_cpy;

	matrix = get_data()->envp_matrix;
	size = ft_matrixsize(matrix);
	new_matrix = malloc_p(sizeof(char *) * size); //
	new_matrix[size - 1] = NULL;
	env_name_cpy = ft_strjoin(env_name, "=");
	if (!env_name_cpy)
	{
		free(new_matrix);
		ft_quit(ERR_MEM, "Error: failed to allocate memory");
	}
	j = 0;
	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], env_name_cpy, name_len + 1) != 0)
			new_matrix[j++] = matrix[i];
		else
			free(matrix[i]);
		i++;
	}
	free(env_name_cpy);
	free(matrix); //non ft_freematrix() altrimenti faccio il free di tutti gli elementi nuovi e vecchi
	get_data()->envp_matrix = new_matrix;
}

void	envp_matrix_replace(char **matrix, t_envp elem, uint32_t name_len, uint32_t value_len)
{
	uint32_t	i;
	char		*tmp;
	char        *env_name_cpy;

	matrix = get_data()->envp_matrix;
	env_name_cpy = ft_strjoin(elem.name, "=");
	if (!env_name_cpy)
		ft_quit(ERR_MEM, "Error: failed to allocate memory");
	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], env_name_cpy, name_len + 1) == 0)
		{
			tmp = matrix[i];
			matrix[i] = (char *)malloc_p(sizeof(char) * name_len + value_len + 2);
			free(tmp);
			ft_strlcpy(matrix[i], env_name_cpy, name_len + 1);
			ft_strcat(matrix[i], elem.value);
		}
		i++;
	}
	free(env_name_cpy);
}

void	envp_matrix_add(char **matrix, t_envp  elem, uint32_t name_len, uint32_t value_len)
{
	char		**new_matrix;
	uint32_t	i;
    size_t      size;

	size = ft_matrixsize(matrix) + 2;
	new_matrix = malloc_p(sizeof(char *) * size);
	new_matrix[size - 1] = NULL;
	i = -1;
	while (matrix[++i])
		new_matrix[i] = matrix[i];
	new_matrix[i] = ft_calloc(name_len + value_len + 2, sizeof(char)); //NON protected altrimenti non facciamo il free della matrice
	if (!new_matrix[i])
	{
		ft_freematrix(new_matrix);
		ft_quit(ERR_MEM, "Error: failed to allocate memory");
	}
	ft_strcpy(new_matrix[i], elem.name);
	new_matrix[i][name_len] = '=';
	ft_strcat(new_matrix[i], elem.value);
	free(matrix);
	get_data()->envp_matrix = new_matrix;
}

//TODO handle cases where there is '=' in the value
//for some reason our export (or env) command adds extra " to the value
void	envp_matrix_print_env(void)
{
	uint8_t		i;
	char		**matrix;

	matrix = get_data()->envp_matrix;
	i = -1;
	while (matrix[++i])
		if (*(ft_strchr(matrix[i], '=') + 1))
			printf("%s\n", matrix[i]);
}

void	envp_matrix_print_export(void)
{
	char		**matrix;
	char		*to_print;
	uint32_t	size;
	uint32_t	name_len;

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

//TODO refactor il sorting di env_matrix_print_export
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
