/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/02/06 12:05:07 by craimond         ###   ########.fr       */
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

	if (!path || !cmd)
		return (NULL);
	if (ft_strnstr(cmd, "/", 1) || ft_strnstr(cmd, "./", 2) || ft_strnstr(cmd, "../", 3))
		return (get_custom_bin(cmd));
	dirs = ft_split(path, ':');
	if (!dirs)
		ft_quit(ERR_MALLOC, "failed to allocate memory");
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
		ft_quit(ERR_MALLOC, "failed to allocate memory");
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

bool	is_shell_space(char c)
{
	static char 	shell_spaces[] = {' ', '\n', '\t'};
	static uint8_t	n_spaces = sizeof(shell_spaces) / sizeof(shell_spaces[0]);
	uint8_t			i;

	i = 0;
	while (i < n_spaces)
		if (c == shell_spaces[i++])
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
		ft_quit(ERR_MALLOC, "failed to allocate memory");
	cmd = ft_strjoin("rm -rf ", tmpdir_name);
	free(tmpdir_name);
	if (!cmd)
		ft_quit(ERR_MALLOC, "failed to allocate memory");
    exec_simple_cmd(getenv("PATH"), cmd);
	free(cmd);
}

void	free_data(t_data *data)
{
	ft_freematrix(data->cmd_args);
	ft_freematrix(data->envp_matrix);
	free(data->cmd_path);
	lstclear(data->lexered_params, &del_content_lexer);
	treeclear(data->parsed_params, &del_content_parser);
	envp_table_clear(data->envp_table);
	close_all_fds();
}

void	close_all_fds(void)
{
	int		fd;

	fd = 1; //senza chiudere stdin e stdout
	while (++fd < MAX_FDS)
		reset_fd(&fd);
}

void	ft_parse_error(char token)
{
	ft_putstr_fd("Parse error near '", 2);
	write(2, &token, 1);
	ft_putstr_fd("'\n", 2);
}

void	ft_syntax_error(char token)
{
	ft_putstr_fd("Syntax error near '", 2);
	write(2, &token, 1);
	ft_putstr_fd("'\n", 2);
}

t_data *get_data(void)
{
	static t_data data;

	return (&data);
}
