/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/02/21 14:54:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

bool	is_shell_space(char c) //meglio cosi' altrimenti complicated conditional
{
	static char 	shell_spaces[] = {' ', '\n', '\t'};
	static uint8_t	n_spaces = sizeof(shell_spaces) / sizeof(shell_spaces[0]);
	uint8_t			i;

	i = 0;
	while (i < n_spaces)
		if (c == shell_spaces[i++])
			return (true);
	return (false);
}

void	ft_quit(uint8_t id, char *msg)
{
	dprintf(2, RED "error : %d\n" DEFAULT, id); //to remove
	if (errno != EINTR)
	{
		while (open("./tmp/print_sem", O_CREAT | O_EXCL, 0666) == EEXIST)
			;
		if (!msg)
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
		else
			ft_putstr_fd(msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		unlink("./tmp/print_sem");
	}
	if (id == EXEC_FAILURE)
		free(msg);
	quit_from_main((uint8_t)id); //quit from main manda SIGTERM a tutti, quindi anche a se stesso. e le free vengono fatte dall'handler di sigterm
}

void	quit_from_main(uint8_t id)
{
	t_data		*data;
	uint8_t 	i;

	i = 0;
	data = get_data();
	while (i < sizeof(id))
	{
		if (0x01 & (id << i++))
			kill(data->main_pid, SIGUSR1);
		else
			kill(data->main_pid, SIGUSR2);
	}
}

void	clean_heredocs(char *path)
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

void	free_data(void)
{
	t_data	*data;

	close_all_fds();
	data = get_data();
	if (!data)
		return ;
	ft_freematrix(data->cmd_args);
	data->cmd_args = NULL;
	ft_freematrix(data->envp_matrix);
	data->envp_matrix = NULL;
	free(data->cmd_path);
	lstclear(data->lexered_params, &del_content_lexer);
	free(data->lexered_params);
	data->lexered_params = NULL;
	treeclear(data->parsed_params, &del_content_parser);
	free(data->parsed_params);
	data->parsed_params = NULL;
	envp_table_clear(data->envp_table);
	free(data->envp_table);
	data->envp_table = NULL;
	free(data->input);
	data->input = NULL;
}

//TODO valutare se unirla con freedata
void	free_builtin_data(void)
{
	t_data	*data;

	data = get_data();
	if (!data)
		return ;
	ft_freematrix(data->cmd_args);
	data->cmd_args = NULL;
	free(data->input);
	data->input = NULL;
	lstclear(data->lexered_params, &del_content_lexer);
	free(data->lexered_params);
	data->lexered_params = NULL;
}

void	close_all_fds(void)
{
	int		fd;

	fd = 2; //senza chiudere stdin e stdout
	while (++fd < MAX_FDS)
		close(fd); //NON close_p perche' la maggiorparte daranno errore
}

void	ft_parse_error(char token)
{
	ft_putstr_fd("Parse error near '", STDERR_FILENO);
	write(STDERR_FILENO, &token, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	ft_syntax_error(char token)
{
	ft_putstr_fd("Syntax error near '", STDERR_FILENO);
	write(STDERR_FILENO, &token, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

t_data *get_data(void)
{
	static t_data data;

	return (&data);
}
