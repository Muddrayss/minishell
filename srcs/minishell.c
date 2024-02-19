/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/02/19 14:42:39 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_status;

static void check_args(int argc, char **argv);
static void	init_general(void);
static void init_data(char **envp);
static void minishell_loop(void);

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

	while (true)
	{
		//TODO gestire linea lunga che supera colonne
		set_signals(S_INTERACTIVE);
		input = readline(RED "mi" YELLOW "ni" GREEN "sh" CYAN "el" PURPLE "l$ " DEFAULT);
		if (!input)
			ft_quit(123, "exit");
		input = ft_strtrim(input, " \t\n");
		if (input[0] == '\0' || is_empty_str(input))
			continue ;
		add_history(input);
		lexered_params = lexer(input);
		execution_tree = parser(lexered_params);
		if (!execution_tree)
			continue ;
		set_signals(S_SILENT);
		executor(execution_tree);
	}
}

bool is_empty_str(char *str)
{
	while (*str)
	{
		if (!is_shell_space(*str))
			return (false);
		str++;
	}
	return (true);
}
