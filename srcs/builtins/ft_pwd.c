/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:42 by egualand          #+#    #+#             */
/*   Updated: 2024/02/17 15:18:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pwd(char **args)
{
	char	*buf;

	(void)args;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("pwd: Error:");
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(buf);
	exit(EXIT_SUCCESS);
}
