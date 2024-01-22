/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/01/22 18:12:52 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	init_signals();
	g_signals.sigint = 0;
	g_signals.in_cmd = 0;
	g_signals.in_heredoc = 0;
	exec_single_cmd(*path, "clear", NULL, data);
}

static void	minishell_loop(t_data *data)
{
	char		*input;
	t_list		*params_head;

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
//va bene per comandi senza here_doc (non essendoci pipe() ne heredoc)
void	exec_single_cmd(char *path, char *cmd_str, t_list *redirs, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_quit(1, NULL, data);
	if (pid == 0)
		exec(path, cmd_str, data);
	else
	{
		// kill(pid, SIGSTOP);
		exec_redirs(redirs, STDIN_FILENO, data);
	}
	// kill(pid, SIGCONT);
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
		ft_quit(COMMAND_NOT_FOUND, ft_strjoin("command not found: ", cmd_args[0]), data);
	else
		execve(data->cmd_path, cmd_args, data->envp);
	ft_quit(EXEC_FAILURE, ft_strjoin("minishell: failed to execute command: ", cmd_args[0]), data);
}
