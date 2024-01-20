/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/01/20 18:03:05 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(char **envp, char **path, t_data *data);
static void minishell_loop(t_data *data);

// static void print_matrix(char **matrix)
// {
// 	unsigned int i;

// 	i = -1;
// 	while (matrix[++i])
// 		printf("%s\n", matrix[i]);
// }

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
	exec_single_cmd(*path, "clear", envp, NULL, data);
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
		executor(params_head, data);
		if (!params_head)
			continue ;
	}
}

void	exec_single_cmd(char *path, char *cmd_str, char **envp, t_list *redirs, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_quit(1, NULL, data);
	if (pid == 0)
	{
		if (redirs)
			exec_redirs(redirs, data);
		exec(path, cmd_str, envp, data);
	}
	else
		wait(NULL);
}

void  exec(char *path, char *cmd_str, char **envp, t_data *data)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd_str, ' ');
	data->cmd_args = cmd_args;
	if (!cmd_args)
		ft_quit(5, "Failed to allocate memory", data);
	data->cmd_path = get_cmd(path, cmd_args[0], data);
	if (!data->cmd_path)
		ft_quit(COMMAND_NOT_FOUND, ft_strjoin("command not found: ", cmd_args[0]), data);
	else
		execve(data->cmd_path, cmd_args, envp);
	ft_quit(EXEC_FAILURE, ft_strjoin("minishell: failed to execute command: ",
					cmd_str), data);
}
