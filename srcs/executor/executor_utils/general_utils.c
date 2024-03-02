/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:48:18 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 00:33:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*clear_quotes(char *str)
{
	uint32_t	i;
	uint32_t	j;
	char		*new_str;
	char		master_quote;

	i = 0;
	j = 0;
	new_str = (char *)malloc_p(sizeof(char) * (ft_strlen(str) + 1));
	master_quote = '\0';
	while (str[i])
	{
		if (!master_quote && (str[i] == '\'' || str[i] == '"'))
			master_quote = str[i];
		else if (master_quote && str[i] == master_quote)
			master_quote = '\0';
		else if (!master_quote || (master_quote && str[i] != master_quote))
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (ft_freenull((void **)&str), new_str);
}

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

	data = get_data();
	data->cmd_args = ft_split(cmd_str, ' ');
	if (!data->cmd_args)
		ft_quit(ERR_MEM, "minishell: failed to allocate memory");
	if (!data->cmd_args[0] || !data->cmd_args[0][0])
	{
		free_data();
		exit(0);
	}
	if (is_builtin(data->cmd_args[0]))
		exec_builtin(data->cmd_args);
	else
	{
		data->cmd_path = get_cmd_path(path, data->cmd_args[0]);
		execve(data->cmd_path, data->cmd_args, data->envp_matrix);
		if (errno != ENOEXEC)
			ft_quit(EXEC_FAILURE, ft_strjoin("minishell: failed to execute command: ", data->cmd_args[0]));
		free_data();
		exit(0);
	}
}

