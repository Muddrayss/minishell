/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:31:02 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 19:12:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	quit_from_main(const uint8_t id);
static void free_data();
static void	close_all_fds(void);

void	ft_quit(const uint8_t id, const char *const msg)
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
	quit_from_main((uint8_t)id);
}

static void	quit_from_main(const uint8_t id)
{
	uint8_t		i;
	const pid_t	main_pid = get_data()->main_pid;

	i = 0;
	while (i < (sizeof(id) * 8))
	{
		if (id & (0x01 << i++))
			kill(main_pid, SIGUSR1);
		else
			kill(main_pid, SIGUSR2);
		usleep(100);
	}
}

void	release_resources(void)
{
	free_data();
	gc_cleanup();
	rl_clear_history();
	close_all_fds();
}

static void free_data()
{
	t_data	*data;

	data = get_data();
	treeclear(&data->envp_tree, free);
	free(data->envp_matrix);
	data->envp_matrix = NULL;
	free(data->starting_dir);
	data->starting_dir = NULL;
}

static void	close_all_fds(void)
{
	uint16_t	fd;

	fd = 0;
	while (fd < MAX_FDS)
		close(fd++);
}
