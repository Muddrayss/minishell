/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/02/02 17:44:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char	*get_custom_bin(char *path);
static char	*get_new_env(char *name, char *value);

char	*get_cmd(char *path, char *cmd)
{
	char			**dirs;
	char			*full_path;
	unsigned int	i;
	unsigned int	size;

	if (ft_strnstr(cmd, "/", 1) || ft_strnstr(cmd, "./", 2) || ft_strnstr(cmd, "../", 3))
		return (get_custom_bin(cmd));
	dirs = ft_split(path, ':');
	if (!dirs)
		ft_quit(3, ft_strdup("failed to allocate memory"));
	full_path = NULL;
	i = -1;
	while (dirs[++i])
	{
		size = ft_strlen(dirs[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(size * sizeof(char));
		if (!full_path)
			ft_quit(3, ft_strdup("failed to allocate memory"));
		ft_strlcpy(full_path, dirs[i], size);
		ft_strlcat(full_path, "/", size);
		ft_strlcat(full_path, cmd, size);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
	}
	ft_free_matrix(dirs);
	if (!full_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	return (full_path);
}

static char	*get_custom_bin(char *path)
{
	char	*full_path;
	char	*tmp;

	full_path = NULL;
	tmp = ft_getenv("PWD");
	ft_strlcat(tmp, "/", ft_strlen(tmp) + 2);
	if (ft_strncmp(path, "../", 3) == 0)
		full_path = ft_strjoin(tmp, path);
	else if (ft_strncmp(path, "./", 2) == 0)
		full_path = ft_strjoin(tmp, path + 2);
	else
		full_path = ft_strdup(path);
	if (!full_path)
		ft_quit(37, "failed to allocate memory");
	if (access(full_path, X_OK) == 0)
    	return (free(tmp), full_path);
	else
	{
		if (errno == EACCES)
			ft_putstr_fd("minishell: permission denied: ", 2);
		else if (errno == ENOENT)
			ft_putstr_fd("minishell: no such file or directory: ", 2);
		else
			ft_putstr_fd("minishell: error accessing file: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
    return (free(tmp), free(full_path), NULL);
}

char	*ft_getenv(char *env_name)
{
	t_data	*data;
	char	*env_value;
	int		env_name_len;
	int		i;

	data = get_data();
	env_value = NULL;
	env_name_len = ft_strlen(env_name);
	i = 0;
	while (ft_strncmp(data->envp[i], env_name, env_name_len) != 0)
		i++;
	if (data->envp[i] != NULL)
	{
		env_value = ft_strdup(data->envp[i] + env_name_len + 1); //per saltare il nome e l'=
		if (!env_value)
			ft_quit(3, "failed to allocate memory");
	}
	return (env_value);
}

void	ft_setenv(char *name, char *value, int8_t overwrite)
{
	t_data	*data;
	size_t	name_len;
	int		i;
	char	*env_name;
	char	**new_env;

	data = get_data();
	name_len = ft_strlen(name);
	if (overwrite)
	{
		i = 0;
		while (data->envp[i])
		{
			env_name = ft_strdup_until(data->envp[i++], "=", NULL);
			if (!env_name)
				ft_quit(4, "failed to allocate memory");
			if (ft_strncmp(env_name, name, name_len) == 0)
				break ;
		}
		free(data->envp[i]);
		data->envp[i] = get_new_env(name, value);
	}
	else
	{
		i = ft_matrixsize(data->envp);
		new_env = malloc(sizeof(char *) * i + 2);
		if (!new_env)
			ft_quit(34, "failed to allocate memory");
		new_env[i + 1] = NULL;
		new_env = ft_strarrncpy(new_env, data->envp, i);
		new_env[i] = get_new_env(name, value);
		ft_free_matrix(data->envp);
		data->envp = new_env;
	}
}

static char	*get_new_env(char *name, char *value)
{
	char	*new_env;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	new_env = ft_strjoin(tmp, value);
	return (free(tmp), free(name), free(value), new_env);
}

bool	is_shell_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (true);
	return (false);
}

void	ft_quit(int id, char *msg)
{
	t_data	*data;

	data = get_data();
	dprintf(2, RED "error : %d\n" DEFAULT, id); //to remove
	if (errno != EINTR)
	{
		while (open_p("./tmp/print_sem", O_CREAT | O_EXCL, 0666) == EEXIST)
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
}

void	clean_heredocs(void)
{
	t_data	*data;
    char    *tmpdir_name;
	char	*cmd;

	data = get_data();
    tmpdir_name = ft_strjoin(data->starting_dir, "/tmp");
	cmd = ft_strjoin("rm -rf ", tmpdir_name);
	free(tmpdir_name);
    exec_simple_cmd(getenv("PATH"), cmd);
	free(cmd);
}

void	free_data(t_data *data)
{
	if (data->cmd_args)
		ft_free_matrix(data->cmd_args);
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->lexered_params)
		ft_lstclear(data->lexered_params, &del_content_lexer);
	//TODO fare una funzione che chiude tutti i fd
}

void	ft_parse_error(char token)
{
	ft_putstr_fd("Parse error near '", 2);
	ft_putchar_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

t_data *get_data(void)
{
	static t_data data;

	return (&data);
}
