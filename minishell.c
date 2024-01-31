/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/01/31 21:42:27 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	g_status;

static void	init(char **envp, char **path);
static void minishell_loop(void);

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	
	(void)argc;
	(void)argv;
	init(envp, &path);
	minishell_loop();
}

static void	init(char **envp, char **path)
{
	t_data	*data;
	
	*path = getenv("PATH");
	data = get_data();
	errno = 0;
	g_status = 0;
	data->envp = ft_strarr_dup(envp);
	data->cmd_args = NULL;
	data->cmd_path = NULL;
	data->lexered_params = NULL;
	data->starting_dir = getenv("PWD");
	exec_simple_cmd(*path, "clear");
	clean_heredocs();
	exec_simple_cmd(*path, "mkdir -p tmp");
}

static void	minishell_loop()
{
	char		*input;
	t_list		*params_head;

	while (1)
	{
		init_signals();
		input = readline(RED "mi" YELLOW "ni" GREEN "sh" CYAN "el" PURPLE "l$ " DEFAULT);
		if (!input)
			ft_quit(123, "exit");
		if (input[0] == '\0')
			continue ;
		add_history(input);
		params_head = lexer(input);
		params_head = parser(params_head);
		if (!params_head)
			continue ;
		executor(params_head);
	}
}
//va bene per comandi interni senza redirs, e senza here_doc e senza salvare l'exit status in data
void	exec_simple_cmd(char *path, char *cmd_str)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_quit(99, NULL);
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
		ft_quit(5, "Failed to allocate memory");
	if (!cmd_args[0])
	{
		free_data(data);
		exit(0);
	}
	data->cmd_path = get_cmd(path, cmd_args[0]);
	if (!data->cmd_path)
	{
		free_data(data);
		exit(COMMAND_NOT_FOUND);
	}
	else
		execve(data->cmd_path, cmd_args, data->envp);
	if (errno != ENOEXEC)
		ft_quit(EXEC_FAILURE, ft_strjoin("minishell: failed to execute command: ", cmd_args[0]));
	exit(0);
}
