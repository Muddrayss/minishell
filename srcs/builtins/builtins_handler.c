/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:55:03 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 16:55:49 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	free_builtins_data(void);

bool is_builtin(const char *const cmd_str)
{
	char 					*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	char					*cmd;
	uint16_t				i;
	static const uint8_t	n_builtins = sizeof(builtins) / sizeof(char *);

	i = 0;
	while (cmd_str[i] && !is_shell_space(cmd_str[i]))
		i++;
	cmd = (char *)malloc_p(sizeof(char) * (i + 1));
	ft_strlcpy(cmd, cmd_str, i + 1);
	i = 0;
	while (i < n_builtins)
		if (ft_strcmp(cmd, builtins[i++]) == 0)
			return (free_and_null((void **)&cmd), true);
	return (free_and_null((void **)&cmd), false);
}

void exec_builtin(const char **const cmd_args)
{
	uint8_t					i;
	static void				(*const builtin_functions[])(const char *const *) = {&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit};
	static const char		*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	static const uint8_t	n_builtins = sizeof(builtins) / sizeof(char *);

	i = 0;
	while (i < n_builtins)
	{
		if (ft_strcmp(cmd_args[0], builtins[i]) == 0)
			builtin_functions[i](cmd_args);
		i++;
	}
	free_builtins_data();
}

static void	free_builtins_data(void)
{
	t_data	*data;

	data = get_data();
	free_and_null((void **)&data->cmd_str);
	free_and_null((void **)&data->cmd_args);
	free_and_null((void **)&data->input);
	lstclear(&data->lexered_params, &del_content_lexer);
	free_and_null((void **)&data->lexered_params);
}
