/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:45:11 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 15:42:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static bool	is_custom_bin(const char *const cmd);
static char	*search_cmd_in_dirs(const char *const entry, const char *const cmd);
static char	*get_custom_bin(const char *const cmd);
static void	throw_error(const char *const cmd);

char	*get_cmd_path(const char *const path, const char *const cmd)
{
	char	*entry;
	char	*full_path;
	char	*path_cpy;

	full_path = NULL;
	if (!path || !cmd)
		return (NULL);
	if (is_custom_bin(cmd))
		return (get_custom_bin(cmd));
	path_cpy = ft_strdup(path, TMP);
	entry = ft_strtok(path_cpy, ':');
	while (entry && !full_path)
	{
		full_path = search_cmd_in_dirs(entry, cmd);
		entry = ft_strtok(NULL, ':');
	}
	if (!entry)
		return (throw_error(cmd), release_resources(), NULL);
	return (full_path);
}

static bool is_custom_bin(const char *const cmd)
{
	uint8_t				i;
	static const char	*prefixes[] = {"./", "../", "/", NULL};

	i = 0;
	while (prefixes[i])
	{
		if (ft_strnstr(cmd, prefixes[i], ft_strlen(prefixes[i])) != NULL)
			return (true);
		i++;
	}
	return (false);
}

static char *search_cmd_in_dirs(const char *const entry, const char *const cmd)
{
	char			*full_path;
	const uint16_t	len = ft_strlen(entry) + ft_strlen(cmd) + 2;

	full_path = (char *)malloc_p(sizeof(char) * len, TMP);
	ft_strcpy(full_path, entry);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (NULL);
}

static char	*get_custom_bin(const char *const cmd)
{
	char		*full_path;
	const char	*cwd = getcwd_p(NULL, 0, TMP);

	full_path = (char *)calloc_p(ft_strlen(cwd) + ft_strlen(cmd) + 2, sizeof(char), TMP);
	if (ft_strncmp(cmd, "../", 3) == 0 || ft_strncmp(cmd, "./", 2) == 0)
	{
		ft_strcpy(full_path, cwd);
		ft_strcat(full_path, "/");
	}
	ft_strcat(full_path, cmd);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	ft_putstr_fd("minishell: error opening file '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (NULL);
}

static void	throw_error(const char *const cmd)
{
	ft_putstr_fd("minishell: command not found: '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
