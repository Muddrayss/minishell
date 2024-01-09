/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/01/09 18:21:45 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **matrix)
{
	unsigned int	i;

	i = -1;
	while (matrix && matrix[++i])
		free(matrix[i]);
	free(matrix);
}

char	*get_cmd(char *path, char *cmd, t_data *data)
{
	char			**dirs;
	char			*full_path;
	unsigned int	i;
	unsigned int	size;

	dirs = ft_split(path, ':');
	if (!dirs)
		ft_quit(3, ft_strdup("failed to allocate memory"), data);
	full_path = NULL;
	i = -1;
	while (dirs[++i])
	{
		size = ft_strlen(dirs[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(size * sizeof(char));
		if (!full_path)
			ft_quit(3, ft_strdup("failed to allocate memory"), data);
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

// diversa da isspace perche' bash non intepreta \v \f e \r come spazi
bool	is_shell_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (true);
	return (false);
}

void	del_content(void *content)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)content;
	if (lexer->type == CMD)
		free(lexer->str.cmd);
	free(lexer);
}

void	ft_quit(int id, char *msg, t_data *data)
{
	if (errno != EINTR)
	{
		if (!msg)
			ft_putstr_fd(strerror(errno), 1);
		else
			ft_putstr_fd(msg, 1);
	}
	if (data && data->lexered_params_head)
		ft_lstclear(data->lexered_params_head, &del_content);
	exit(id);
	return ;
}
