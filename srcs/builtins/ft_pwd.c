/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:42 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pwd(t_cc *const *args)
{
	char	*pwd;

	(void)args;
	pwd = getcwd_p(NULL, 0, TMP);
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
