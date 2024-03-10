/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:55:03 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 15:16:01 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	is_builtin(t_cc *const cmd_str)
{
	const char				*builtins[]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	char					*cmd;
	uint16_t				i;
	static const uint8_t	n_builtins = sizeof(builtins) / sizeof(char *);

	i = 0;
	while (cmd_str[i] && !is_shell_space(cmd_str[i]))
		i++;
	cmd = (char *)malloc_p(sizeof(char) * (i + 1), TMP);
	ft_strlcpy(cmd, cmd_str, i + 1);
	i = 0;
	while (i < n_builtins)
		if (ft_strcmp(cmd, builtins[i++]) == 0)
			return (true);
	return (false);
}

void	exec_builtin(t_cc **const cmd_args)
{
	uint8_t					i;
	static void				(*builtin_functions[])(t_cc *const *)
		= {&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit};
	static t_cc				*builtins[]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	static const uint8_t	n_builtins = sizeof(builtins) / sizeof(char *);

	i = 0;
	while (i < n_builtins)
	{
		if (ft_strcmp(cmd_args[0], builtins[i]) == 0)
			builtin_functions[i](cmd_args);
		i++;
	}
}
