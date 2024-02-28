/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:26:11 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 21:31:12 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	clean_heredocs(char *path);

void	check_args(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		exit(1);
	}	
	if (!envp || !*envp)
	{
		ft_putstr_fd("minishell: failed to initialize environvment\n", STDERR_FILENO);
		exit(ERR_ENV);
	}
}

void	init_data(char **envp)
{
	t_data	*data;
	
	data = get_data();
	data->cmd_args = NULL;
	data->cmd_path = NULL;
	data->lexered_params = NULL;
	data->starting_dir = getcwd_p(NULL, 0);
	data->main_pid = getpid();
	data->input = NULL;
	if (!data->starting_dir)
		ft_quit(ERR_ENV, "minishell: failed to initialize environment");
	data->envp_matrix = calloc_p(ft_matrixsize(envp) + 1, sizeof(char *));
	envp_table_init(envp);
}

void init_general(void)
{
	char	*path;
	
	set_bad_errnos();
	path = ft_getenv("PATH");
	g_status = 0;
	exec_simple_cmd(path, "clear");
	clean_heredocs(path);
	exec_simple_cmd(path, "mkdir -p tmp");
}

static void	clean_heredocs(char *path)
{
	t_data	*data;
	char	*cmd;

	data = get_data();
	cmd = (char *)calloc_p(ft_strlen(data->starting_dir) + 12, sizeof(char));
	ft_strcpy(cmd, "rm -rf ");
	ft_strcat(cmd, data->starting_dir);
	ft_strcat(cmd, "/tmp");
    exec_simple_cmd(path, cmd);
	free(cmd);
}
