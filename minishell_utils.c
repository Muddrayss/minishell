/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/01/20 18:02:35 by egualand         ###   ########.fr       */
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

void	ft_lstdel_if(t_list **lst, bool (*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*to_free;

	tmp = *lst;
	prev = NULL;
	to_free = NULL;
	while (tmp)
	{
		if (f(tmp->content) == true)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = tmp->next;
			to_free = tmp;
		}
		else
		{
			prev = tmp;
			to_free = NULL;
		}
		tmp = tmp->next;
		ft_lstdelone(to_free, del); // se to_free e' null, non fa nulla
	}
}

void	ft_quit(int id, char *msg, t_data *data)
{
	if (errno != EINTR)
	{
		if (!msg)
			ft_putstr_fd(strerror(errno), 1);
		else
			ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
	if (data)
	{
		if (data->cmd_args)
			free_matrix(data->cmd_args);
		if (data->cmd_path)
			free(data->cmd_path);
		if (data->lexered_params)
			ft_lstclear(data->lexered_params, &del_content_lexer);
	}
	exit(id);
	return ;
}

int8_t	ft_parse_error(char token)
{
	ft_putstr_fd("Parse error near '", 1);
	ft_putchar_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	return (-1);
}
