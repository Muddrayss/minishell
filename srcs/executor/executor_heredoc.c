/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:34:01 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 15:24:33 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static uint8_t	fic(t_cc *const limiter, const uint16_t heredoc_fd);
static void		fill_heredoc(t_cc *const limiter, const uint16_t fd);

void	create_heredocs(const t_tree *const tree, uint8_t *const s)
{
	t_parser	*elem;
	t_list		*redirs;
	t_redir		*redir;
	char		*f;

	if (!tree || *s != 0)
		return ;
	elem = (t_parser *)tree->content;
	if (elem->type == CMD)
	{
		redirs = (t_list *)elem->cmd->redirs;
		while (redirs)
		{
			redir = (t_redir *)redirs->content;
			redirs = redirs->next;
			if (redir->type != REDIR_HEREDOC)
				continue ;
			f = get_heredoc_filename(redir->heredoc_fileno);
			*s = fic(redir->filename, open_p(f, 01101, 0644));
			if (*s != 0)
				return ;
		}
	}
	create_heredocs(tree->left, s);
	create_heredocs(tree->right, s);
}

char	*get_heredoc_filename(const uint16_t id)
{
	char				*filename;
	const t_data *const	data = get_data();
	t_cc *const			id_str = ft_itoa((uint16_t)id);
	const uint16_t		size = ft_strlen(data->starting_dir)
		+ ft_strlen(id_str) + 16;

	filename = ft_calloc(size, sizeof(char));
	if (!filename || !id_str)
		return (panic(ERR_MEM, "minishell: failed to allocate memory"), NULL);
	ft_strcpy(filename, data->starting_dir);
	ft_strcat(filename, "/tmp/.heredoc_");
	ft_strcat(filename, id_str);
	return (filename);
}

static uint8_t	fic(t_cc *const limiter, const uint16_t heredoc_fd)
{
	int32_t		status;
	const pid_t	pid = fork_p();

	if (pid == 0)
	{
		set_signals(S_HEREDOC, false);
		fill_heredoc(limiter, heredoc_fd);
	}
	else
	{
		waitpid_p(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	return ((uint8_t)status);
}

static void	fill_heredoc(t_cc *const limiter, const uint16_t fd)
{
	char		*str;
	uint16_t	str_len;

	str = NULL;
	while (true)
	{
		str = readline("> ");
		if (!str)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			break ;
		}
		str_len = ft_strlen(str);
		if (ft_strncmp(limiter, str, str_len + 1) == 0)
			break ;
		replace_env_vars(&str, true);
		ft_putstr_fd(str, fd);
		write(fd, "\n", 1);
	}
	release_resources();
	exit(0);
}
