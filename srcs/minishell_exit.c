/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:31:02 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 17:33:10 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	quit_from_main(uint8_t id);
static void	close_all_fds(void);

void	ft_quit(uint8_t id, char *msg)
{
	if (errno != EINTR)
	{
		while (open("./tmp/print_sem", O_CREAT | O_EXCL, 0666) == EEXIST)
			;
		if (!msg)
			perror("minishell");
		else
			ft_putstr_fd(msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		unlink("./tmp/print_sem");
	}
	if (id == EXEC_FAILURE)
		free(msg);
	quit_from_main((uint8_t)id);
}

static void	quit_from_main(uint8_t id)
{
	t_data		*data;
	uint8_t 	i;

	i = 0;
	data = get_data();
	while (i < (sizeof(id) * 8))
	{
		if (id & (0x01 << i++))
			kill(data->main_pid, SIGUSR1);
		else
			kill(data->main_pid, SIGUSR2);
		usleep(100);
	}
}

//TODO free_and_null non sarebbe male ft_free_and_null(void **ptr)
void	free_data(void)
{
	t_data	*data;

	close_all_fds();
	data = get_data();
	free(data->starting_dir);
	data->starting_dir = NULL;
	ft_freematrix(data->cmd_args);
	data->cmd_args = NULL;
	ft_freematrix(data->envp_matrix);
	data->envp_matrix = NULL;
	envp_tree_clear(data->envp_tree);
	data->envp_tree = NULL;
	free(data->cmd_path);
	lstclear(data->lexered_params, &del_content_lexer);
	free(data->lexered_params);
	data->lexered_params = NULL;
	treeclear(data->parsed_params, &del_content_parser);
	free(data->parsed_params);
	data->parsed_params = NULL;
	free(data->input);
	data->input = NULL;
}

static void	close_all_fds(void)
{
	int		fd;

	fd = 2; //senza chiudere stdin e stdout
	while (++fd < MAX_FDS)
		close(fd); //NON close_p perche' la maggiorparte daranno errore
}
