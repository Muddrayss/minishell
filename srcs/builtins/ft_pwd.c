/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:42 by egualand          #+#    #+#             */
/*   Updated: 2024/02/19 15:44:13 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pwd(char **args)
{
	char	*buf;

	(void)args;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("pwd: ");
		g_status = EXIT_FAILURE;
		return ;
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(buf);
	g_status = EXIT_SUCCESS;
}
