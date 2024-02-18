/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:08:20 by egualand          #+#    #+#             */
/*   Updated: 2024/02/18 14:31:17 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_cd(char **args)
{
	char *cwd;

	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	cwd = getcwd(NULL, 0);
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
	ft_setenv("OLDPWD", cwd, true);
	free(cwd);
	cwd = getcwd(NULL, 0);
	ft_setenv("PWD", cwd, true);
	exit(EXIT_SUCCESS);
}