/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/01/04 18:56:47 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **matrix)
{
	unsigned int i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

char	*get_cmd(char *path, char *cmd)
{
	char **dirs;
	char *full_path;
	unsigned int i;
	unsigned int size;

	// TODO valutare se usare strtok per non dovere fare malloc e free con split
	dirs = ft_split(path, ':');
	full_path = NULL;
	i = -1;
	while (dirs[++i])
	{
		size = ft_strlen(dirs[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(size * sizeof(char));
		if (!full_path)
			break ;
		ft_strlcpy(full_path, dirs[i], size);
		ft_strlcat(full_path, "/", size);
		ft_strlcat(full_path, cmd, size);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
	}
	free_matrix(dirs);
	return (full_path);
}