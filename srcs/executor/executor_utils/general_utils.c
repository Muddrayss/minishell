/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:48:18 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 19:14:42 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	clear_quotes(char **const str)
{
	uint32_t	i;
	uint32_t	j;
	char		*new_str;
	char		master_quote;

	j = 0;
	i = 0;
	master_quote = '\0';
	new_str = (char *)malloc_p(sizeof(char) * (ft_strlen(*str) + 1));
	while ((*str)[i])
	{
		if (!master_quote && ((*str)[i] == '\'' || (*str)[i] == '"'))
			master_quote = (*str)[i];
		else if (master_quote && (*str)[i] == master_quote)
			master_quote = '\0';
		else if (!master_quote || (master_quote && (*str)[i] != master_quote))
			new_str[j++] = (*str)[i];
		i++;
	}
	new_str[j] = '\0';
	//free_and_null((void **)str);
	*str = new_str;
}

void	exec_simple_cmd(const char *const path, const char *const cmd_str)
{
	pid_t				pid;
	const char *const 	cmd = strdup_p(cmd_str);

	pid = fork_p();
	if (pid == 0)
		exec(path, cmd);
	free_and_null((void **)&cmd);
	wait(NULL);
}

void  exec(const char *const path, const char *const cmd_str)
{
	t_data	*data;
	char	*cmd_path;

	data = get_data();
	data->cmd_args = get_cmd_args((char *)cmd_str);
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



