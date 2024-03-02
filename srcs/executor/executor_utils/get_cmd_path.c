/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:45:11 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 19:36:14 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static bool is_custom_bin(char *cmd);
static char *search_cmd_in_dirs(char *entry, char *cmd);
static char *get_custom_bin(char *path);
static void throw_cmd_not_found_error(char *cmd);

char	*get_cmd_path(char *path, char *cmd)
{
    char *entry;
    char *full_path;
	char *path_cpy;

	full_path = NULL;
	if (!path || !cmd)
		return (NULL);
	if (is_custom_bin(cmd))
		return (get_custom_bin(cmd));
	path_cpy = strdup_p(path);
    entry = ft_strtok(path_cpy, ':');
	while (entry && !full_path)
	{
    	full_path = search_cmd_in_dirs(entry, cmd);
		entry = ft_strtok(NULL, ':');
	}
	free_and_null((void **)&path_cpy);
    if (!entry)
		return (throw_cmd_not_found_error(cmd), free_data(), NULL);
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

static char *search_cmd_in_dirs(char *entry, char *cmd)
{
    char		*full_path;
	uint16_t	len;

	len = ft_strlen(entry) + ft_strlen(cmd) + 2; // +2 for '/' and '\0'
	full_path = (char *)malloc_p(sizeof(char) * len);
	ft_strcpy(full_path, entry);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
    if (access(full_path, X_OK) == 0)
		return (full_path);
    return (free_and_null((void **)&full_path), NULL);
}

static char	*get_custom_bin(char *cmd)
{
	char	*full_path;
	char	*cwd;

	cwd = getcwd_p(NULL, 0);
	full_path = (char *)calloc_p(ft_strlen(cwd) + ft_strlen(cmd) + 2, sizeof(char));
	if (ft_strncmp(cmd, "../", 3) == 0 || ft_strncmp(cmd, "./", 2) == 0)
	{
		ft_strcpy(full_path, cwd);
		ft_strcat(full_path, "/");
	}
	free(cwd);
	ft_strcat(full_path, cmd);
	if (access(full_path, X_OK) == 0)
    	return (full_path);
	ft_putstr_fd("minishell: error opening file '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
    return (free_and_null((void **)&full_path), NULL);
}

static void throw_cmd_not_found_error(char *cmd)
{
	ft_putstr_fd("minishell: command not found: '", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}