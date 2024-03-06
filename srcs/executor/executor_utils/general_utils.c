/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:48:18 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 11:44:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	exec_simple_cmd(const char *const path, char *cmd_str)
{
	pid_t	pid;

	pid = fork_p();
	if (pid == 0)
		exec(path, strdup_p(cmd_str));
	wait(NULL);
}

void	exec(const char *const path, char *cmd_str)
{
	t_data	*data;
	char	*cmd_path;
	char	**cmd_args;

	data = get_perm_data();
	cmd_args = get_cmd_args(cmd_str);
	if (!cmd_args[0] || !cmd_args[0][0])
	{
		release_resources();
		exit(0);
	}
	if (is_builtin(cmd_args[0]))
		exec_builtin((const char **)cmd_args);
	else
	{
		cmd_path = get_cmd_path(path, cmd_args[0]);
		if (!cmd_path)
			exit(CMD_NOT_FOUND);
		execve(cmd_path, cmd_args, data->envp_matrix);
		if (errno != ENOEXEC)
			ft_quit(EXEC_FAILURE, strjoin_p("minishell: failed to execute command: ", cmd_args[0]));
		release_resources();
		exit(0);
	}
}
