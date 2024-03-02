/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:31:02 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 22:57:55 by craimond         ###   ########.fr       */
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
		free_and_null((void **)&msg);
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

void	free_data(void)
{
	t_data	*data;

	close_all_fds();
	data = get_data();
	free_and_null((void **)&data->starting_dir);
	if (data->cmd_args)
		free_and_null((void **)&data->cmd_args[0]);
	free_and_null((void **)&data->cmd_args);
	treeclear(&data->envp_tree, &free);
	free_and_null((void **)&data->envp_matrix);
	data->envp_matrix = NULL;
	lstclear(&data->lexered_params, &del_content_lexer);
	treeclear(&data->parsed_params, &del_content_parser);
	free_and_null((void **)&data->input);
}

static void	close_all_fds(void)
{
	uint16_t	fd;

	fd = 2; //senza chiudere stdin e stdout
	while (++fd < MAX_FDS)
		close(fd); //NON close_p perche' la maggiorparte daranno errore
}
