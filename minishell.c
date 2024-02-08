/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/02/08 14:24:52 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	g_status;

static void check_args(int argc, char **argv);
static void	init_general(void);
static void init_data(char **envp);
static void minishell_loop(void);
static bool str_is_empty(char *str);

int	main(int argc, char **argv, char **envp)
{
	check_args(argc, argv);
	init_data(envp);
	init_general();
	minishell_loop();
}

static void	check_args(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		exit(1);
	}
}

static void	init_data(char **envp)
{
	t_data	*data;
	
	data = get_data();
	data->cmd_args = NULL;
	data->cmd_path = NULL;
	data->lexered_params = NULL;
	data->starting_dir = getenv("PWD");
	if (!data->starting_dir)
		ft_quit(ERR_ENV, "Failed to get current working directory\nEnv var PWD likely not set");
	data->envp_matrix = calloc_p(ft_matrixsize(envp) + 1, sizeof(char *));
	envp_table_init(envp);
}

static void init_general(void)
{
	char	*path;
	
	path = ft_getenv("PATH");
	errno = 0;
	g_status = 0;
	exec_simple_cmd(path, "clear");
	clean_heredocs(path);
	exec_simple_cmd(path, "mkdir -p tmp");
}

static void	minishell_loop()
{
	char		*input;
	t_list		*lexered_params;
	t_tree		*execution_tree;

	while (1)
	{
		input = readline(RED "mi" YELLOW "ni" GREEN "sh" CYAN "el" PURPLE "l$ " DEFAULT);
		if (!input)
			ft_quit(123, "exit"); 
		if (input[0] == '\0' || str_is_empty(input))
			continue ;
		add_history(input);
		lexered_params = lexer(input);
		execution_tree = parser(lexered_params);
		if (!execution_tree)
			continue ;
		executor(execution_tree);
	}
}

static bool str_is_empty(char *str)
{
	while (*str)
	{
		if (!is_shell_space(*str))
			return (false);
		str++;
	}
	return (true);
}

//va bene per comandi interni senza redirs, e senza here_doc e senza salvare l'exit status in data
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
	char	**cmd_args;

	data = get_data();
	cmd_args = ft_split(cmd_str, ' ');
	data->cmd_args = cmd_args;
	if (!cmd_args)
		ft_quit(ERR_MALLOC, "Failed to allocate memory");
	if (!cmd_args[0])
	{
		free_data();
		exit(0);
	}
	data->cmd_path = get_cmd(path, cmd_args[0]);
	if (!data->cmd_path)
	{
		free_data();
		exit(COMMAND_NOT_FOUND);
	}
	else
		execve(data->cmd_path, cmd_args, data->envp_matrix);
	if (errno != ENOEXEC)
		ft_quit(EXEC_FAILURE, ft_strjoin("minishell: failed to execute command: ", cmd_args[0]));
	exit(0);
}
