/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:55:03 by egualand          #+#    #+#             */
/*   Updated: 2024/02/18 18:07:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool is_builtin(char *cmd_str)
{
	char	*cmd;
	char 	*end;
	char 	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	uint8_t	n_builtins;
	
	cmd = ft_strdup(cmd_str);
	if (!cmd)
		ft_quit(ERR_MALLOC, "Failed to allocate memory");
	end = ft_strchr(cmd, ' ');
	if (end)
		*end = '\0';
	n_builtins = sizeof(builtins) / sizeof(char *);
	while (n_builtins--)
		if (ft_strcmp(cmd, builtins[n_builtins]) == 0)
			return (free(cmd), true);
	return (free(cmd), false);
}

//I BUILTINS VENGONO ESEGUITI IN UN FIGLIO!! QUINDI IN OGNI CASO EXPORT, CD, UNSET NON POSSONO MODIFICARE LE VARIABILI D'AMBIENTE DEL PADRE
void exec_builtin(char *cmd_str)
{
	char	**cmd_args;
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	void	(*builtin_functions[])(char **) = {&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit};
	uint8_t	n_builtins;

	cmd_str = replace_env_vars(cmd_str);
	//cmd_str = replace_wildcards(cmd_str);
	cmd_args = ft_split(cmd_str, ' ');
	get_data()->cmd_args = cmd_args;
	if (!cmd_args)
		ft_quit(ERR_MALLOC, "Failed to allocate memory");
	n_builtins = sizeof(builtins) / sizeof(char *);
	while (n_builtins--)
		if (ft_strcmp(cmd_args[0], builtins[n_builtins]) == 0)
			builtin_functions[n_builtins](cmd_args);
}