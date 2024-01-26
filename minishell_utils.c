/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/01/26 16:28:13 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char	*get_custom_bin(char *path, char **envp);

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

	if (ft_strnstr(cmd, "/", 1) || ft_strnstr(cmd, "./", 2) || ft_strnstr(cmd, "../", 3))
		return (get_custom_bin(cmd, data->envp));
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
	if (!full_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	return (full_path);
}

static char	*get_custom_bin(char *path, char **envp, t_data *data)
{
	char	*full_path;
	char	*tmp;

	full_path = NULL;
	tmp = ft_getenv(envp, "PWD");
	ft_strlcat(tmp, "/", ft_strlen(tmp) + 2);
	if (ft_strncmp(path, "../", 3) == 0)
		full_path = ft_strjoin(tmp, path);
	else if (ft_strncmp(path, "./", 2) == 0)
		full_path = ft_strjoin(tmp, path + 2);
	else
		full_path = ft_strdup(path);
	if (!full_path)
		ft_quit(37, "failed to allocate memory", data);
	if (access(full_path, X_OK) == 0)
		return (free(tmp), full_path);
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
	return (free(tmp), free(full_path), NULL);
}

char	*ft_getenv(t_data *data, char *env_name)
{
	char	*env_value;
	int		env_name_len;
	int		i;

	env_value = NULL;
	env_name_len = ft_strlen(env_name);
	i = 0;
	while (ft_strncmp(data->envp[i], env_name, env_name_len) != 0)
		i++;
	if (data->envp[i] != NULL)
	{
		env_value = ft_strdup(data->envp[i] + env_name_len + 1); //per saltare il nome e l'=
		if (!env_value)
			ft_quit(3, "failed to allocate memory", data);
	}
	return (env_value);
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
	dprintf(2, RED "error : %d\n" DEFAULT, id); //to remove
	if (errno != EINTR)
	{
		while (open("./tmp/print_sem", O_CREAT | O_EXCL, 0666) == EEXIST)
			;
		if (!msg)
			ft_putstr_fd(strerror(errno), 2);
		else
			ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		unlink("./tmp/print_sem");
	}
	if (data)
		free_data(data);
	exit(id);
	return ;
}

void clean_heredocs(t_data *data)
{
    char    *tmpdir_name;
	char	*cmd;

    tmpdir_name = ft_strjoin(data->starting_dir, "/tmp");
	cmd = ft_strjoin("rm -rf ", tmpdir_name);
	free(tmpdir_name);
    exec_simple_cmd(getenv("PATH"), cmd, data);
	free(cmd);
}

void	free_data(t_data *data)
{
	if (data->cmd_args)
		free_matrix(data->cmd_args);
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->lexered_params)
		ft_lstclear(data->lexered_params, &del_content_lexer);
	//TODO fare una funzione che chiude tutti i fd
}

int8_t	ft_parse_error(char token)
{
	ft_putstr_fd("Parse error near '", 2);
	ft_putchar_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}
