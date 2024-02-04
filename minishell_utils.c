/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/02/04 18:44:28 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char	*get_custom_bin(char *path);
// static char	*get_new_env(char *name, char *value);

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
		ft_quit(3, "failed to allocate memory");
	full_path = NULL;
	i = -1;
	while (dirs[++i])
	{
		size = ft_strlen(dirs[i]) + ft_strlen(cmd) + 2;
		full_path = malloc_p(size * sizeof(char));
		ft_strcpy(full_path, dirs[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
	}
	ft_freematrix(dirs);
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
	ft_strcat(tmp, "/");
	if (ft_strncmp(path, "../", 3) == 0)
		full_path = ft_strjoin(tmp, path);
	else if (ft_strncmp(path, "./", 2) == 0)
		full_path = ft_strjoin(tmp, path + 2);
	else
		full_path = ft_strdup(path);
	if (!full_path)
		ft_quit(3, "failed to allocate memory");
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

void	ft_setenv(char *name, char *value, bool overwrite)
{
	t_data	*data;
	size_t	name_len;
	int		i;
	char	*env_name;
	char	**new_env;

	data = get_data();
	name_len = ft_strlen(name);
	if (overwrite == true)
	{
		i = 0;
		while (data->envp[i])
		{
			env_name = get_env_name
			if (ft_strncmp(env_name, name, MAX(env_name_len, name_len)) == 0)
				break ;
		}
		free(data->envp[i]);
		data->envp[i] = get_new_env(name, value);
	}
	else
	{
		i = ft_matrixsize(data->envp);
		new_env = malloc_p(sizeof(char *) * i + 2);
		new_env[i + 1] = NULL;
		new_env = ft_strarrncpy(new_env, data->envp, i);
		new_env[i] = get_new_env(name, value);
		ft_freematrix(data->envp);
		data->envp = new_env;
	}
}

// static char	*get_new_env(char *name, char *value)
// {
// 	char	*new_env;
// 	char	*tmp;

// 	tmp = ft_strjoin(name, "=");
// 	free(name);
// 	if (!tmp)
// 		return(free(value), ft_quit(3, "failed to allocate memory"), NULL);
// 	new_env = ft_strjoin(tmp, value);
// 	free(tmp);
// 	free(value);
// 	if (!new_env)
// 		return(ft_quit(3, "failed to allocate memory"), NULL);
// 	return (new_env);
// }

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
	if (id == EXEC_FAILURE)
		free(msg);
	exit(id);
}

void	clean_heredocs(void)
{
	t_data	*data;
    char    *tmpdir_name;
	char	*cmd;

	data = get_data();
    tmpdir_name = ft_strjoin(data->starting_dir, "/tmp");
	if (!tmpdir_name)
		ft_quit(3, "failed to allocate memory");
	cmd = ft_strjoin("rm -rf ", tmpdir_name);
	free(tmpdir_name);
	if (!cmd)
		ft_quit(3, "failed to allocate memory");
    exec_simple_cmd(getenv_p("PATH"), cmd);
	free(cmd);
}

void	free_data(t_data *data)
{
	if (data->cmd_args)
		ft_freematrix(data->cmd_args);
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->lexered_params)
		lstclear(data->lexered_params, &del_content_lexer);
	//TODO fare una funzione che chiude tutti i fd
}

void	ft_parse_error(char token)
{
	ft_putstr_fd("Parse error near '", 2);
	write(2, &token, 1);
	ft_putstr_fd("'\n", 2);
}

t_data *get_data(void)
{
	static t_data data;

	return (&data);
}
