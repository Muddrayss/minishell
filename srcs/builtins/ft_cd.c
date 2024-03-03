/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:08:20 by egualand          #+#    #+#             */
/*   Updated: 2024/03/03 16:54:04 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_cd(const char *const *args)
{
	char	*cwd;

	if (!args[1])
		return ;
	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		g_status = EXIT_FAILURE;
		return ;
	}
	cwd = getcwd_p(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		g_status = EXIT_FAILURE;
		return ;
	}
	if (chdir_p(args[1]) == -1)
	{
		perror("cd");
		g_status = EXIT_FAILURE;
		free_and_null((void **)&cwd);
		return ;
	}
	ft_setenv("OLDPWD=", cwd, true);
	free_and_null((void **)&cwd);
	cwd = getcwd_p(NULL, 0);
	if (!cwd)
		return ;
	ft_setenv("PWD=", cwd, true);
	free_and_null((void **)&cwd);
	g_status = EXIT_SUCCESS;
}
