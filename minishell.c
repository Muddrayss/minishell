/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/01/15 18:43:49 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(char **envp, char **path, t_data *data);
static void	exec_cmd(char *path, char **envp, char **cmd_args, t_data *data);
static void	minishell_loop(char *path, char **envp, t_data *data);

// TODO sig handler che setti la variabile errno a EINTR
// TODO per i comandi da implementare custom usare execve per creare il .bin (se non e' gia' presente) compilando con cc il file corrispondente
// TODO colori

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	t_data	data;

	(void)argc;
	(void)argv;
	init(envp, &path, &data);
	minishell_loop(path, envp, &data);
}

static void	minishell_loop(char *path, char **envp, t_data *data)
{
	char	*input;
	t_list	*params_head;

	// TODO appendere '>' extra in base alla profondita'
	while (1)
	{
		input = readline(AQUA "minishell$ " DEFAULT);
		if (!input)
			ft_quit(123, "exit\n", data);
		if (input[0] == '\0')
			continue ;
		add_history(input);
		params_head = lexer(input, data);
		params_head = parser(params_head, data);
		
		// while (params_head)
		// {
		// 	t_parser *content = (t_parser *)params_head->content;
		// 	ft_putstr_fd(content->cmd_str, 1);
		// 	if (content->env_vars)
		// 	{
		// 		while (*content->env_vars)
		// 		{
		// 			printf(" %s", *content->env_vars);
		// 			content->env_vars++;
		// 		}
		// 	}
		// 	if (content->redirs)
		// 	{
		// 		t_list *redirs = content->redirs;
		// 		while (redirs)
		// 		{
		// 			t_redir *redir = (t_redir *)redirs->content;
		// 			printf("input: %d, output: %d, filname: %s", redir->fds[0], redir->fds[1], redir->filename);
		// 			redirs = redirs->next;
		// 		}
		// 	}
		// 	printf("\n");
		// 	params_head = params_head->next;
		// }

		if (!params_head)
			continue ;
		(void)params_head;
		(void)path;
		(void)envp;
		(void)data;
	}
}

static void	init(char **envp, char **path, t_data *data)
{
	errno = 0;
	*path = getenv("PATH");
	data->cmd_args = NULL;
	data->cmd_path = NULL;
	data->lexered_params = NULL;
	init_signals();
	exec_cmd(*path, ft_split("clear", ' '), envp, data);
}

static void	exec_cmd(char *path, char **cmd_args, char **envp, t_data *data)
{
	pid_t	pid;
	int		status;

	data->cmd_args = cmd_args;
	pid = fork();
	if (pid == -1)
		ft_quit(1, NULL, data);
	if (pid == 0)
	{
		if (!cmd_args)
			ft_quit(5, ft_strdup("failed to allocate memory"), data);
		data->cmd_path = get_cmd(path, cmd_args[0], data);
		printf("%s\n", data->cmd_path);
		if (!data->cmd_path)
			ft_quit(3, ft_strjoin("command not found: ", cmd_args[0]), data);
		else
			execve(data->cmd_path, cmd_args, envp);
		ft_quit(2, NULL, data);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			ft_quit(5, NULL, data);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ft_quit(6, ft_strjoin("minishell: failed to execute command: ",
					cmd_args[0]), data);
	}
}
