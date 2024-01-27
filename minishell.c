/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/01/27 15:15:39 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

t_signals	g_signals;

static void	init(char **envp, char **path, t_data *data);
static void minishell_loop(t_data *data);

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	t_data 	data;

	(void)argc;
	(void)argv;
	init(envp, &path, &data);
	minishell_loop(&data);
}

static void	init(char **envp, char **path, t_data *data)
{
	errno = 0;
	*path = getenv("PATH");
	data->envp = ft_strarr_dup(envp);
	data->cmd_args = NULL;
	data->cmd_path = NULL;
	data->lexered_params = NULL;
	data->starting_dir = getenv("PWD");
	init_signals();
	g_signals.sigint = 0;
	g_signals.in_cmd = 0;
	g_signals.in_heredoc = 0;
	exec_simple_cmd(*path, "clear", data);
	clean_heredocs(data);
	exec_simple_cmd(*path, "mkdir -p tmp", data);
}

static void	minishell_loop(t_data *data)
{
	char		*input;
	t_list		*params_head;

	//write(1, "\n", 1); //cosi' piu' minishell nested non stanno accanto quando si preme ctrl+c
	while (1)
	{
		input = readline(RED "mi" YELLOW "ni" GREEN "sh" CYAN "el" PURPLE "l$ " DEFAULT);
		if (!input)
			ft_quit(123, "exit", data);
		if (input[0] == '\0')
			continue ;
		add_history(input);
		params_head = lexer(input, data);
		params_head = parser(params_head, data);
		g_signals.in_cmd = 1;
		g_signals.sigint = 0;
		executor(params_head, data);
		g_signals.in_cmd = 0;
		if (!params_head)
			continue ;
	}
}
//va bene per comandi senza redirs, e senza here_doc
void	exec_simple_cmd(char *path, char *cmd_str, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_quit(99, NULL, data);
	if (pid == 0)
		exec(path, cmd_str, data);
	wait(NULL);
}

void  exec(char *path, char *cmd_str, t_data *data)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd_str, ' ');
	data->cmd_args = cmd_args;
	if (!cmd_args)
		ft_quit(5, "Failed to allocate memory", data);
	if (!cmd_args[0])
	{
		free_data(data);
		exit(0);
	}
	data->cmd_path = get_cmd(path, cmd_args[0], data);
	if (!data->cmd_path)
	{
		free_data(data);
		exit(COMMAND_NOT_FOUND);
	}
	else
		execve(data->cmd_path, cmd_args, data->envp);
	if (errno != ENOEXEC)
		ft_quit(EXEC_FAILURE, ft_strjoin("minishell: failed to execute command: ", cmd_args[0]), data);
	exit(0);
}
