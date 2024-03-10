/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:48:18 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 15:17:47 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	exec_simple_cmd(t_cc *const path, char *cmd_str)
{
	pid_t	pid;

	pid = fork_p();
	if (pid == 0)
		exec(path, ft_strdup(cmd_str, TMP));
	wait(NULL);
}

void	exec(t_cc *const path, char *cmd_str)
{
	t_data	*data;
	char	*cmd_path;
	char	**cmd_args;

	data = get_data();
	cmd_args = get_cmd_args(cmd_str);
	if (!cmd_args[0] || !cmd_args[0][0])
		release_resources();
	if (!cmd_args[0] || !cmd_args[0][0])
		exit(0);
	if (is_builtin(cmd_args[0]))
		exec_builtin((t_cc **)cmd_args);
	else
	{
		cmd_path = get_cmd_path(path, cmd_args[0]);
		if (!cmd_path)
			exit(CMD_NOT_FOUND);
		execve(cmd_path, cmd_args, data->envp_matrix);
		if (errno != ENOEXEC)
			panic(EXEC_FAILURE,
				ft_strjoin("minishell: failed to execute command: ",
					cmd_args[0], TMP));
		release_resources();
		exit(0);
	}
}
