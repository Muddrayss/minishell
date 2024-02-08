/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/02/08 16:38:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char	*get_custom_bin(char *path);
static void	throw_file_error(char *file);
static char *search_cmd_in_dirs(char **dirs, char *cmd);
static char *concat_path_cmd(char *dir, char *cmd);
static bool is_custom_bin(char *cmd);

char *get_cmd(char *path, char *cmd)
{
    char **dirs;
    char *full_path;

	full_path = NULL;
    if (!path || !cmd)
        return (NULL);
    if (is_custom_bin(cmd))
        return (get_custom_bin(cmd));
    dirs = ft_split(path, ':');
    if (!dirs)
        ft_quit(ERR_MALLOC, "failed to allocate memory");
    full_path = search_cmd_in_dirs(dirs, cmd);
    ft_freematrix(dirs);
    if (!full_path)
	{
        ft_putstr_fd("minishell: command not found: '", STDERR_FILENO);
        ft_putstr_fd(cmd, STDERR_FILENO);
        ft_putstr_fd("'\n", STDERR_FILENO);
    }
    return (full_path);
}

static bool is_custom_bin(char *cmd)
{
	int8_t		i;
	static char	*prefixes[] =
	{"./", "../", "/", NULL};
	
	i = -1;
	while (prefixes[++i])	
		if (ft_strnstr(cmd, prefixes[i], ft_strlen(prefixes[i])) != NULL)
			return (true);
	return (false);
} 

static char *concat_path_cmd(char *dir, char *cmd)
{
	unsigned int size;
	char *full_path;

	size = strlen(dir) + strlen(cmd) + 2; // +2 for '/' and '\0'
	full_path = malloc_p(size);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
    ft_strcat(full_path, cmd);
    return (full_path);
}

static char *search_cmd_in_dirs(char **dirs, char *cmd)
{
    char	*full_path;
	int		i;

	full_path = NULL;
	i = -1;
    while (dirs[++i])
	{
        full_path = concat_path_cmd(dirs[i], cmd);
        if (access(full_path, X_OK) == 0)
			return (full_path);
        free(full_path);
    }
    return (NULL);
}

static char	*get_custom_bin(char *path)
{
	char	*full_path;
	char	*tmp;
	char    *tmp2;

	full_path = NULL;
	tmp2 = ft_getenv("PWD");
	tmp = ft_strjoin(tmp2, "/"); //abbastanza ridicolo dover usare strjoin per aggiungere un carattere
	free(tmp2);
	if (!tmp)
		ft_quit(ERR_MALLOC, "failed to allocate memory");
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
		throw_file_error(path);
    return (free(tmp), free(full_path), NULL);
}

//quanto cazzo e' bello unire stringhe in C porca puttana. per unire 2 stringhe e 1 carattere novantamila malloc
static void	throw_file_error(char *file)
{
	char	*tmp;
	char	*error_str;
	
	tmp = ft_strjoin("minishell: Error opening file '", file);
	if (!tmp)
		ft_quit(ERR_MALLOC, "failed to allocate memory");
	error_str = ft_strjoin(tmp, "'");
	free(tmp);
	if (!error_str)
		ft_quit(ERR_MALLOC, "failed to allocate memory");
	perror(error_str); //viene tipo: minishell: Error opening file 'file.txt': No such file or directory
	free(error_str);
}

bool	is_shell_space(char c) //meglio cosi' altrimenti complicated conditional
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
	dprintf(2, RED "error : %d\n" DEFAULT, id); //to remove
	if (errno != EINTR)
	{
		while (open("./tmp/print_sem", O_CREAT | O_EXCL, 0666) == EEXIST)
			;
		if (!msg)
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
		else
			ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		unlink("./tmp/print_sem");
	}
	free_data();
	if (id == EXEC_FAILURE)
		free(msg);
	exit(id);
}

void	clean_heredocs(char *path)
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
    exec_simple_cmd(path, cmd);
	free(cmd);
}

void	free_data(void)
{
	t_data	*data;

	close_all_fds();
	data = get_data();
	if (!data)
		return ;
	ft_freematrix(data->cmd_args);
	ft_freematrix(data->envp_matrix);
	free(data->cmd_path);
	lstclear(data->lexered_params, &del_content_lexer);
	treeclear(data->parsed_params, &del_content_parser);
	envp_table_clear(data->envp_table);
}

void	close_all_fds(void)
{
	int		fd;

	fd = 2; //senza chiudere stdin e stdout
	while (++fd < MAX_FDS)
		close(fd); //NON close_p perche' la maggiorparte daranno errore
}

void	ft_parse_error(char token)
{
	ft_putstr_fd("Parse error near '", STDERR_FILENO);
	write(STDERR_FILENO, &token, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	ft_syntax_error(char token)
{
	ft_putstr_fd("Syntax error near '", STDERR_FILENO);
	write(STDERR_FILENO, &token, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

t_data *get_data(void)
{
	static t_data data;

	return (&data);
}
