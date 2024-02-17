/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:08:20 by egualand          #+#    #+#             */
/*   Updated: 2024/02/17 15:04:41 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char *get_absolute_from_relative_path(char *path);
static void update_env_vars(char *new_path);

void ft_cd(char **args)
{
	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (chdir(args[1]) == -1)
	{
		//forse si piò usare perror direttamente
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	update_env_vars(args[1]);
	exit(EXIT_SUCCESS);
}

static char *get_absolute_from_relative_path(char *path)
{
	char	*buf;
	char	*new_path;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("cd: Error:");
		exit(EXIT_FAILURE);
	}
	new_path = ft_strjoin(buf, "/");
	free(buf);
	if (new_path == NULL)
		return (NULL);
	buf = ft_strjoin(new_path, path);
	free(new_path);
	return (buf);
}

static void update_env_vars(char *new_path)
{
	char	*oldpwd;
	char	*pwd;
	char	*new_path_absolute;

	oldpwd = ft_getenv("OLDPWD");
	pwd = ft_getenv("PWD");
	if (new_path[0] == '/')
		new_path_absolute = ft_strdup(new_path);
	else
		new_path_absolute = get_absolute_from_relative_path(new_path);
	if (oldpwd)
		ft_setenv("OLDPWD", pwd, true);
	else
		ft_setenv("OLDPWD", pwd, false);
	if (pwd)
		ft_setenv("PWD", new_path_absolute, true);
	else
		ft_setenv("PWD", new_path_absolute, false);
	free(oldpwd);
	free(pwd);
	free(new_path_absolute);
}