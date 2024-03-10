/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:08:20 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int8_t	cd_check_args(t_cc *const *args);
static char		*cd_getcwd(void);

void	ft_cd(t_cc *const *args)
{
	char	*tmp;

	if (cd_check_args(args) == -1)
		return ;
	tmp = cd_getcwd();
	if (!tmp)
		return ;
	if (chdir_p(args[1]) == -1)
	{
		perror("cd");
		g_status = EXIT_FAILURE;
		return ;
	}
	ft_setenv("OLDPWD=", tmp, true);
	tmp = cd_getcwd();
	if (!tmp)
		return ;
	ft_setenv("PWD=", tmp, true);
	g_status = EXIT_SUCCESS;
}

static int8_t	cd_check_args(t_cc *const *args)
{
	if (!args[1])
		return (-1);
	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		g_status = EXIT_FAILURE;
		return (-1);
	}
	return (0);
}

static char	*cd_getcwd(void)
{
	char	*cwd;

	cwd = getcwd_p(NULL, 0, TMP);
	if (!cwd)
	{
		perror("cd");
		g_status = EXIT_FAILURE;
		return (NULL);
	}
	return (cwd);
}
