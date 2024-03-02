/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:55:03 by egualand          #+#    #+#             */
/*   Updated: 2024/03/02 19:12:09 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool is_builtin(char *cmd_str)
{
	char		*cmd;
	uint32_t	len;
	char 		*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	uint8_t		n_builtins;
	
	len = 0;
	while (cmd_str[len] && !is_shell_space(cmd_str[len]))
		len++;
	cmd = (char *)malloc_p(sizeof(char) * (len + 1));
	ft_strlcpy(cmd, cmd_str, len + 1);
	n_builtins = sizeof(builtins) / sizeof(char *);
	while (n_builtins--)
		if (ft_strcmp(cmd, builtins[n_builtins]) == 0)
			return (free_and_null((void **)&cmd), true);
	return (free_and_null((void **)&cmd), false);
}

void exec_builtin(char **cmd_args)
{
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	void	(*builtin_functions[])(char **) = {&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit};
	uint8_t	n_builtins;
	t_data	*data;

	data = get_data();
	n_builtins = sizeof(builtins) / sizeof(char *);
	while (n_builtins--)
		if (ft_strcmp(cmd_args[0], builtins[n_builtins]) == 0)
			builtin_functions[n_builtins](cmd_args);
	if (data->cmd_args)
		free_and_null((void **)&data->cmd_args[0]);
	free_and_null((void **)&data->cmd_args);	
	free_and_null((void **)&data->input);
	lstclear(&data->lexered_params, &del_content_lexer);
	free_and_null((void **)&data->lexered_params);
}
