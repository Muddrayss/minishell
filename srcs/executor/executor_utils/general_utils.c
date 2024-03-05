/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:48:18 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 16:59:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	exec_simple_cmd(const char *const path, const char *const cmd_str)
{
	pid_t				pid;
	const char *const	cmd = strdup_p(cmd_str);

	pid = fork_p();
	if (pid == 0)
		exec(path, cmd);
	free_and_null((void **)&cmd);
	wait(NULL);
}

void	exec(const char *const path, const char *const cmd_str)
{
	t_data	*data;
	char	*cmd_path;

	data = get_data();
	data->cmd_str = strdup_p(cmd_str);
	data->cmd_args = get_cmd_args(&data->cmd_str);
	if (!data->cmd_args[0] || !data->cmd_args[0][0])
	{
		free_data();
		exit(0);
	}
	if (is_builtin(data->cmd_args[0]))
		exec_builtin((const char **)data->cmd_args);
	else
	{
		cmd_path = get_cmd_path(path, data->cmd_args[0]);
		if (!cmd_path)
			exit(CMD_NOT_FOUND);
		execve(cmd_path, data->cmd_args, data->envp_matrix);
		if (errno != ENOEXEC)
			ft_quit(EXEC_FAILURE, strjoin_p("minishell: failed to execute command: ", data->cmd_args[0]));
		free_data();
		exit(0);
	}
}
