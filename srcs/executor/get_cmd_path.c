/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:45:11 by craimond          #+#    #+#             */
/*   Updated: 2024/02/12 00:10:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_custom_bin(char *path);
static void	throw_file_error(char *file);
static char *search_cmd_in_dirs(char **dirs, char *cmd);
static char *concat_path_cmd(char *dir, char *cmd);
static bool is_custom_bin(char *cmd);

char *get_cmd_path(char *path, char *cmd)
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
	uint32_t	size;
	char 		*full_path;

	size = ft_strlen(dir) + ft_strlen(cmd) + 2; // +2 for '/' and '\0'
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