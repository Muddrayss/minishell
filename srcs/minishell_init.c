/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:26:11 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 23:05:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	clean_heredocs(const char *const path);

void	check_args(const int argc, const char **const argv, const char **const envp)
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

void	init_data(const char **const envp)
{
	t_data	*const	data = get_data();

	data->starting_dir = getcwd_p(NULL, 0);
	data->main_pid = getpid();
	envp_init(envp);
}

void	init_general(void)
{
	char	*path;

	set_errnos();
	path = ft_getenv("PATH=");
	g_status = 0;
	exec_simple_cmd(path, "clear");
	clean_heredocs(path);
	exec_simple_cmd(path, "mkdir -p tmp");
}

static void	clean_heredocs(const char *const path)
{
	const t_data *const	data = get_data();
	char				*cmd;

	cmd = (char *)calloc_p(ft_strlen(data->starting_dir) + 12, sizeof(char));
	ft_strcpy(cmd, "rm -rf ");
	ft_strcat(cmd, data->starting_dir);
	ft_strcat(cmd, "/tmp");
	exec_simple_cmd(path, cmd);
}
