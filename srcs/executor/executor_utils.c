/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:46:56 by craimond          #+#    #+#             */
/*   Updated: 2024/02/20 16:04:38 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	exec_simple_cmd(char *path, char *cmd_str)
{
	pid_t	pid;

	pid = fork_p();
	if (pid == 0)
		exec(path, cmd_str);
	wait(NULL);
}

void  exec(char *path, char *cmd_str)
{
	t_data	*data;
	char	**cmd_args;

	data = get_data();
	cmd_args = ft_split(cmd_str, ' ');
	data->cmd_args = cmd_args;
	if (!cmd_args)
		ft_quit(ERR_MEM, "Error: failed to allocate memory");
	if (cmd_args[0][0] == '\0')
	{
		free_data();
		exit(0);
	}
	if (is_builtin(cmd_args[0]))
		exec_builtin(cmd_args);
	else
	{
		data->cmd_path = get_cmd_path(path, cmd_args[0]);
		if (!data->cmd_path)
		{
			free_data();
			exit(COMMAND_NOT_FOUND);
		}
		else
			execve(data->cmd_path, cmd_args, data->envp_matrix);
		if (errno != ENOEXEC)
			ft_quit(EXEC_FAILURE, ft_strjoin("minishell: failed to execute command: ", cmd_args[0]));
		exit(0);
	}
}