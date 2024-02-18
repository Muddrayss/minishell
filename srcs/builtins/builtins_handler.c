/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:55:03 by egualand          #+#    #+#             */
/*   Updated: 2024/02/18 14:57:33 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

void exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(args);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args);
}