/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/19 17:27:47 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	add_left_right_fds(int *fd, char *cmd, uint8_t flag);
static void		add_filename(char **filename, char *cmd, t_data *data);

void	handle_redir_l(t_list *lexered_params, t_parser *content_par, t_data *data)
{
	t_redir				*redir_content;
	t_lexer				*next_cmd_elem;
	t_token				next_token;
	unsigned int		token_streak;
	static const char	ph_redir = -42;

	// placeholder per le redir
	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory", data);
	redir_content->fds[0] = -42;
	redir_content->fds[1] = STDIN_FILENO;
	redir_content->filename = NULL;
	redir_content->type = REDIR_INPUT_FD;
	next_cmd_elem = get_next_cmd_elem(lexered_params);
	token_streak = check_token_streak(&next_token, lexered_params);
	if (token_streak == 2 && next_token == REDIR_L)
	{
		redir_content->type = REDIR_HEREDOC;
		if (next_cmd_elem)
			add_filename(&redir_content->filename, next_cmd_elem->str.cmd, data);
	}
	else if (token_streak > 3)
	{
		ft_parse_error('<');
		free(redir_content);
		return ;
	}
	else
	{
		if (next_cmd_elem)
		{
			if (add_left_right_fds(&redir_content->fds[1], next_cmd_elem->str.cmd, RIGHT) == -1)
			{
				redir_content->type = REDIR_INPUT;
				if (next_cmd_elem)
					add_filename(&redir_content->filename, next_cmd_elem->str.cmd, data);
			}
		}
	}
	ft_lstadd_front(&content_par->redirs, ft_lstnew(redir_content));
	ft_strlcat(content_par->cmd_str, &ph_redir, ft_strlen(content_par->cmd_str) + 2);
}

void	handle_redir_r(t_list *lexered_params, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data)
{
	t_redir				*redir_content;
	t_lexer				*next_cmd_elem;
	t_token				next_token;
	unsigned int		token_streak;
	static const char	ph_redir = -42;

	// placeholder per le redir
	// TODO valutare se implementare un "same token streak"
	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory", data);
	redir_content->fds[0] = STDOUT_FILENO;
	redir_content->fds[1] = -42;
	redir_content->filename = NULL;
	redir_content->type = REDIR_OUTPUT_FD;
	next_cmd_elem = get_next_cmd_elem(lexered_params);
	token_streak = check_token_streak(&next_token, lexered_params);
	if (token_streak > 3)
	{
		ft_parse_error('>');
		free(redir_content);
		return ;
	}
	if (next_cmd_elem)
		if (add_left_right_fds(&redir_content->fds[1], next_cmd_elem->str.cmd, RIGHT) == -1)
			add_filename(&redir_content->filename, next_cmd_elem->str.cmd, data);
	if (prev_cmd_elem)
		add_left_right_fds(&redir_content->fds[0], prev_cmd_elem->str.cmd, LEFT);
	if (redir_content->fds[1] == -42)
	{
		redir_content->type = REDIR_OUTPUT;
		if (token_streak == 2 && next_token == REDIR_R)
			redir_content->type = REDIR_APPEND;
	}
	if (redir_content->type != REDIR_APPEND && token_streak == 2 && next_token == REDIR_R)
		redir_content->type = REDIR_APPEND_FD;
	ft_lstadd_front(&content_par->redirs, ft_lstnew(redir_content));
	ft_strlcat(content_par->cmd_str, &ph_redir, ft_strlen(content_par->cmd_str) + 2);
}

static int8_t	add_left_right_fds(int *fd, char *cmd, uint8_t flag)
{
	unsigned int	i;

	if (flag == LEFT)
	{
		i = ft_strlen(cmd) - 1;
		while (cmd[i] && ft_isdigit(cmd[i]))
			i--;
	}
	else
	{
		i = 0;
		if (cmd[i] == '&')
			// TODO gestire il parse error in caso di piu' caratteri '&' di fila
			i++;
		while (cmd[i] && ft_isdigit(cmd[i]) == 1)
			i++;
		// guardare atoi qui, tornare indietro all inizio del numero
	}
	// TODO	gestire il caso di un FD che supera MAX INT (direttamente in atoi)
	if ((is_shell_space(cmd[i]) || cmd[i] == '\0') && i > 0)
		*fd = ft_atoi(cmd + i * (flag == LEFT) + 1 * (flag == RIGHT && *cmd == '&'));
	else
		return (-1);
	return (0);
}

static void	add_filename(char **filename, char *cmd, t_data *data)
{
	unsigned int	i;
	char			*name;

	name = NULL;
	// TODO gestire il caso in cui c'e' un token tipo & prima del filename
	i = 0;
	while (cmd[i] != '\0' && is_shell_space(cmd[i]))
		i++;
	name = ft_strdup(&cmd[i]);
	if (!name)
		ft_quit(16, "failed to allocate memory", data);
	while (cmd[i] != '\0' && !is_shell_space(cmd[i]))
		i++;
	name[i] = '\0';
	if (name[0] == PH_INVALID_ENV)
	{
		free(name);
		name = NULL;
	}
	free(*filename);
	*filename = name;
}
