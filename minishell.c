/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/01/05 17:34:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init(char **envp, char **path, t_data *data);
static void exec_cmd(char *path, char **envp, char **cmd_args, t_data *data);
static void	minishell_loop(void);

//TODO sig handler che setti la variabile errno a EINTR

int	main(int argc, char **argv, char **envp)
{
	char 	*path;
	t_data	data;

	(void)argc;
	(void)argv;

	init(envp, &path, &data);
	minishell_loop();
}

static void	minishell_loop(void)
{
	char 	*input;
	char	prompt[20 + 20];

	ft_bzero(prompt, 20);
	ft_strlcat(prompt, "\033[1;35mmini>>", 20);
	//TODO appendere '>' extra in base alla profondita'
	ft_strlcat(prompt, "\033[1;0m ", 20);
	while (1)
	{
		input =	readline(prompt);
		printf("%s\n", input);
	}
}

static void init(char **envp, char **path, t_data *data)
{
	*path = getenv("PATH");
	exec_cmd(*path, envp, ft_split("clear", ' '), data);
}

static void exec_cmd(char *path, char **envp, char **cmd_args, t_data *data)
{
	pid_t	pid;
	int		status;

	data->cmd_args = cmd_args;
	pid = fork();
	if (pid == -1)
		ft_quit(1, NULL);
	if (pid == 0)
	{
		if (!cmd_args)
			ft_quit(5, ft_strdup("failed to allocate memory"));
		data->cmd_path = get_cmd(path, cmd_args[0]);
		printf("%s\n", data->cmd_path);
		if (!data->cmd_path)
			ft_quit(3, ft_strjoin("command not found: ", cmd_args[0]));
		else
			execve(data->cmd_path, cmd_args, envp);
		ft_quit(2, NULL);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			ft_quit(5, NULL);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ft_quit(6, ft_strjoin("minishell: failed to execute command: ", cmd_args[0]));
	}
}

void	ft_quit(int id, char *msg)
{
	if (errno != EINTR)
	{
		if (!msg)
			ft_putstr_fd(strerror(errno), 1);
		else
			ft_putstr_fd(msg, 1);
	}
	exit(id);
	return ;
}