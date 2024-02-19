/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:08:20 by egualand          #+#    #+#             */
/*   Updated: 2024/02/18 22:20:21 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_cd(char **args)
{
	char	*cwd;

	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		g_status = EXIT_FAILURE;
		return ;
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
		g_status = EXIT_FAILURE;
		free(cwd);
		return ;
	}
	ft_setenv("OLDPWD", cwd, true); //se fai la free di cwd, OLDPWD punta a un indirizzo di memoria che non esiste più perche' setenv NON fa una copia della stringa
	free(cwd);
	cwd = getcwd(NULL, 0);
	ft_setenv("PWD", cwd, true);
	free(cwd);
	g_status = EXIT_SUCCESS;
}