/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:42 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 21:36:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pwd(const char *const *args)
{
	char	*pwd;

	(void)args;
	pwd = getcwd_p(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: PWD environvment variable not set\n", STDERR_FILENO);
		g_status = EXIT_FAILURE;
		return ;
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_status = EXIT_SUCCESS;
}
