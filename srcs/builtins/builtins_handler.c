/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:55:03 by egualand          #+#    #+#             */
/*   Updated: 2024/02/29 14:32:00 by egualand         ###   ########.fr       */
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
			return (free(cmd), true);
	return (free(cmd), false);
}

void exec_builtin(char **cmd_args)
{
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	void	(*builtin_functions[])(char **) = {&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit};
	uint8_t	n_builtins;
	t_data	*data;

	n_builtins = sizeof(builtins) / sizeof(char *);
	while (n_builtins--)
		if (ft_strcmp(cmd_args[0], builtins[n_builtins]) == 0)
			builtin_functions[n_builtins](cmd_args);
	data = get_data();
	ft_freematrix(data->cmd_args);
	data->cmd_args = NULL;
	free(data->input);
	data->input = NULL;
	lstclear(data->lexered_params, &del_content_lexer);
	free(data->lexered_params);
	data->lexered_params = NULL;
}
