/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/10 15:04:57 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_left_right_fds(int *fd, char *cmd, uint8_t flag, t_data *data);
static void	add_left_right_filenames(char **filename, char *cmd, uint8_t flag, t_data *data);

void	handle_redir_l(t_list *lexered_params, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data)
{
	t_redir			*redir_content;
	t_lexer			*next_cmd_elem;
	t_token			next_token;
	unsigned int	token_streak;

	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory", data);
	redir_content->input.fd = -42;
	redir_content->output.fd = STDIN_FILENO;
    redir_content->type = REDIR_INPUT_FD;
    next_cmd_elem = get_next_cmd_elem(lexered_params);
	token_streak = check_token_streak(&next_token, lexered_params);
	if (token_streak == 2 && next_token == REDIR_L)
	{
        redir_content->type = REDIR_HEREDOC;
		add_left_right_filenames(&redir_content->input.filename, next_cmd_elem->str.cmd, RIGHT, data);
	}
	else if (token_streak >= 2)
	{
		ft_putstr_fd("Parse error near '<'", 1);
		free(redir_content);
		return ;
	}
    else
    {
	    add_left_right_fds(&redir_content->output.fd, next_cmd_elem->str.cmd, RIGHT, data);
	    if (redir_content->output.fd == -42)
        {
            redir_content->type = REDIR_INPUT;
		    add_left_right_filenames(&redir_content->input.filename, prev_cmd_elem->str.cmd, LEFT, data);
        }
    }
	content_par->redirections = NULL;
	ft_lstadd_front(&content_par->redirections, ft_lstnew(redir_content));
}

void	handle_redir_r(t_list *lexered_params, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data)
{
	t_redir			*redir_content;
	t_lexer			*next_cmd_elem;
	t_token			next_token;
	unsigned int	token_streak;

	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory", data);
	redir_content->input.fd = STDOUT_FILENO;
	redir_content->output.fd = -42;
    redir_content->type = REDIR_OUTPUT_FD;
	next_cmd_elem = get_next_cmd_elem(lexered_params);
	token_streak = check_token_streak(&next_token, lexered_params);
	add_left_right_fds(&redir_content->output.fd, next_cmd_elem->str.cmd, RIGHT, data);
	add_left_right_fds(&redir_content->output.fd, next_cmd_elem->str.cmd, LEFT, data);
    if (redir_content->output.fd == -42)
    {
        redir_content->type = REDIR_OUTPUT;
        if (token_streak == 2 && next_token == REDIR_R)
            redir_content->type = REDIR_APPEND;
        add_left_right_filenames(&redir_content->output.filename, next_cmd_elem->str.cmd, RIGHT, data);
    }
	if (redir_content->type != REDIR_APPEND && token_streak == 2 && next_token == REDIR_R)
		redir_content->type = REDIR_APPEND_FD;
	else if (token_streak >= 2)
	{
		ft_putstr_fd("Parse error near '>'", 1);
		free(redir_content);
		return ;
	}
	content_par->redirections = NULL;
	ft_lstadd_front(&content_par->redirections, ft_lstnew(redir_content));
}

static void	add_left_right_fds(int *fd, char *cmd, uint8_t flag, t_data *data)
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
			i++;
		while (cmd[i] && ft_isdigit(cmd[i]))
			i++;
	}
	if (is_shell_space(cmd[i]))
		*fd = ft_atoi(cmd + i * (flag == LEFT));
}

static void	add_left_right_filenames(char **filename, char *cmd, uint8_t flag, t_data *data)
{
	unsigned int	i;
	char			*tmp;
	char			*filename;

	if (flag == LEFT)
	{
		i = ft_strlen(cmd) - 1;
		while (cmd[i] && is_shell_space(cmd[i]))
			i--;
		while (cmd[i] && !is_shell_space(cmd[i]))
			i--;
		tmp = ft_strdup(&cmd[i + 1]);
		if (!tmp)
			ft_quit(16, "failed to allocate memory", data);
		*filename = ft_strtrim(tmp, " \n\t");
		free(tmp);
		if (!*filename)
			ft_quit(16, "failed to allocate memory", data);
	}
	else if (flag == RIGHT)
	{
		i = 0;
		while (cmd[i] && is_shell_space(cmd[i]))
			i++;
		*filename = ft_strdup(&cmd[i]);
		if (!*filename)
			ft_quit(16, "failed to allocate memory", data);
		while (cmd[i] && !is_shell_space(cmd[i]))
			i++;
		*filename[i] = '\0';
	}
}
