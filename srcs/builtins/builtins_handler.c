/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:55:03 by egualand          #+#    #+#             */
/*   Updated: 2024/02/18 15:21:33 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool is_builtin(char *cmd)
{
	char 	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	uint8_t	n_builtins;
	
	n_builtins = sizeof(builtins) / sizeof(char *);
	while (n_builtins--)
		if (ft_strcmp(cmd, builtins[n_builtins]) == 0)
			return (true);
	return (false);
}

void exec_builtin(char **args)
{
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	void	(*builtin_functions[])(char **) = {&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit};
	uint8_t	n_builtins;
	
	n_builtins = sizeof(builtins) / sizeof(char *);
	while (n_builtins--)
		if (ft_strcmp(args[0], builtins[n_builtins]) == 0)
			builtin_functions[n_builtins](args);
}