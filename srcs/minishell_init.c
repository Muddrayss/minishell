/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:26:11 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 13:33:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	clean_heredocs(char *path);

void	check_args(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
		exit(1);
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
		ft_quit(ERR_ENV, "Error: failed to initialize environment");
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

//TODO refactor con malloc_p
static void	clean_heredocs(char *path)
{
	t_data	*data;
    char    *tmpdir_name;
	char	*cmd;

	data = get_data();
    tmpdir_name = ft_strjoin(data->starting_dir, "/tmp");
	if (!tmpdir_name)
		ft_quit(ERR_MEM, "Error: failed to allocate memory");
	cmd = ft_strjoin("rm -rf ", tmpdir_name);
	free(tmpdir_name);
	if (!cmd)
		ft_quit(ERR_MEM, "Error: failed to allocate memory");
    exec_simple_cmd(path, cmd);
	free(cmd);
}
