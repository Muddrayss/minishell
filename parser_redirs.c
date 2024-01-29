/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/29 20:46:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static int8_t	add_left_right_fds(int *fd, char *cmd, uint8_t flag);
static void		add_filename(char **filename, char *cmd);

bool	handle_redir_l(t_list *lexered_params, t_parser *content_par)
{
	t_redir				*redir_content;
	t_lexer				*next_cmd_elem;
	t_token				next_token;
	unsigned int		token_streak;
	static const char	placeholder = PH_REDIR;

	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory");
	redir_content->fds[0] = -42;
	redir_content->fds[1] = STDOUT_FILENO;
	redir_content->filename = NULL;
	redir_content->type = REDIR_INPUT_FD;
	next_cmd_elem = get_next_cmd_elem(lexered_params);
	token_streak = check_token_streak(&next_token, lexered_params);
	if (token_streak == 2 && next_token == REDIR_L)
	{
		redir_content->type = REDIR_HEREDOC;
		add_filename(&redir_content->filename, next_cmd_elem->str.cmd);
	}
	else
	{
		if (token_streak > 3)
		{
			ft_parse_error('<');
			free(redir_content);
			return (true * (next_token == REDIR_L));
		}
		else
		{
			if (next_cmd_elem)
			{
				if (add_left_right_fds(&redir_content->fds[1], next_cmd_elem->str.cmd, RIGHT) == -1)
				{
					redir_content->type = REDIR_INPUT;
					if (next_cmd_elem)
						add_filename(&redir_content->filename, next_cmd_elem->str.cmd);
				}
			}
		}	
	}
	ft_lstadd_back(&content_par->redirs, ft_lstnew(redir_content));
	ft_strlcat(content_par->cmd_str, &placeholder, ft_strlen(content_par->cmd_str) + 2);
	return (true * (next_token == REDIR_L));
}

bool	handle_redir_r(t_list *lexered_params, t_lexer *prev_cmd_elem, t_parser *content_par)
{
	t_redir				*redir_content;
	t_lexer				*next_cmd_elem;
	t_token				next_token;
	unsigned int		token_streak;
	static const char	placeholder
		 = PH_REDIR;

	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory");
	redir_content->fds[0] = STDIN_FILENO;
	redir_content->fds[1] = -42;
	redir_content->filename = NULL;
	redir_content->type = REDIR_OUTPUT_FD;
	next_cmd_elem = get_next_cmd_elem(lexered_params);
	token_streak = check_token_streak(&next_token, lexered_params);
	if (token_streak > 3)
	{
		ft_parse_error('>');
		free(redir_content);
		return (true * (next_token == REDIR_R));
	}
	if (next_cmd_elem)
		if (add_left_right_fds(&redir_content->fds[1], next_cmd_elem->str.cmd, RIGHT) == -1)
			add_filename(&redir_content->filename, next_cmd_elem->str.cmd);
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
	ft_lstadd_back(&content_par->redirs, ft_lstnew(redir_content));
	ft_strlcat(content_par->cmd_str, &placeholder, ft_strlen(content_par->cmd_str) + 2);
	return (true * (next_token == REDIR_R));
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
		while (cmd[i] && ft_isdigit(cmd[i]))
			i++;
		// guardare atoi qui, tornare indietro all inizio del numero
	}
	// TODO	gestire il caso di un FD che supera MAX INT (direttamente in atoi)
	//TODO gestire caso con tot di spazi dopo & (<&       3);
	if ((is_shell_space(cmd[i]) || cmd[i] == '\0') && i > 0)
		*fd = ft_atoi(cmd + i * (flag == LEFT) + 1 * (flag == RIGHT && *cmd == '&'));
	else
		return (-1);
	return (0);
}

static void	add_filename(char **filename, char *cmd)
{
	unsigned int	i;
	char			*new_str;

	// TODO gestire il caso in cui c'e' un token tipo & prima del filename
	i = 0;
	while (cmd[i] != '\0' && is_shell_space(cmd[i]))
		i++;
	new_str = ft_strdup(cmd + i);
	if (!new_str)
		ft_quit(12, "failed to allocate memory");
	i = 0;
	while (new_str[i] != '\0' && !is_shell_space(new_str[i]))
		i++;
	new_str[i] = '\0';
	free(*filename);
	*filename = new_str;
}
