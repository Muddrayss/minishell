/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/15 15:53:41 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	add_left_right_fds(int *fd, char *cmd, uint8_t flag);
static void		add_left_right_filenames(char **filename, char *cmd, uint8_t flag, t_data *data);

void	handle_redir_l(t_list *lexered_params, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data)
{
	t_redir				*redir_content;
	t_lexer				*next_cmd_elem;
	t_token				next_token;
	unsigned int		token_streak;
	//placeholder per le redir
	static const char	ph_redir
		= -42;

	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory", data);
	redir_content->fds[0] = -42;
	redir_content->fds[1] = STDIN_FILENO;
    redir_content->type = REDIR_INPUT_FD;
    next_cmd_elem = get_next_cmd_elem(lexered_params);
	token_streak = check_token_streak(&next_token, lexered_params);
	if (token_streak == 2 && next_token == REDIR_L)
	{
        redir_content->type = REDIR_HEREDOC;
		add_left_right_filenames(&redir_content->filename, next_cmd_elem->str.cmd, RIGHT, data);
	}
	else if (token_streak >= 2)
	{
		ft_putstr_fd("Parse error near '<'\n", 1);
		free(redir_content);
		return ;
	}
    else
    {
	    add_left_right_fds(&redir_content->fds[1], next_cmd_elem->str.cmd, RIGHT);
	    if (redir_content->fds[1] == -42)
        {
            redir_content->type = REDIR_INPUT;
		    add_left_right_filenames(&redir_content->filename, prev_cmd_elem->str.cmd, LEFT, data);
        }
    }
	content_par->redirs = NULL;
	ft_lstadd_front(&content_par->redirs, ft_lstnew(redir_content));
	ft_strlcat(content_par->cmd_str, &ph_redir, ft_strlen(content_par->cmd_str) + 1);
}

void	handle_redir_r(t_list *lexered_params, t_parser *content_par, t_data *data)
{
	t_redir				*redir_content;
	t_lexer				*next_cmd_elem;
	t_token				next_token;
	unsigned int		token_streak;
	unsigned int		same_token_streak; // $%^^^&
	//placeholder per le redir
	static const char	ph_redir
		= -42;

	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory", data);
	redir_content->fds[0] = STDOUT_FILENO;
	redir_content->fds[1] = -42;
    redir_content->type = REDIR_OUTPUT_FD;
	next_cmd_elem = get_next_cmd_elem(lexered_params);
	token_streak = check_token_streak(&next_token, lexered_params);
	same_token_streak = 0;
	if (token_streak > 3)
	{
		ft_putstr_fd("Parse error near: '>'\n", 1);
		free(redir_content);
		return ;
	}
	if (add_left_right_fds(&redir_content->fds[1], next_cmd_elem->str.cmd, RIGHT) == -1)
		add_left_right_filenames(&redir_content->filename, next_cmd_elem->str.cmd, RIGHT, data);
	add_left_right_fds(&redir_content->fds[1], next_cmd_elem->str.cmd, LEFT);
    if (redir_content->fds[1] == -42)
    {
        redir_content->type = REDIR_OUTPUT;
        if (token_streak == 2 && next_token == REDIR_R)
            redir_content->type = REDIR_APPEND;
        add_left_right_filenames(&redir_content->filename, next_cmd_elem->str.cmd, RIGHT, data);
    }
	if (redir_content->type != REDIR_APPEND && token_streak == 2 && next_token == REDIR_R)
		redir_content->type = REDIR_APPEND_FD;

	content_par->redirs = NULL;
	ft_lstadd_front(&content_par->redirs, ft_lstnew(redir_content));
	ft_strlcat(content_par->cmd_str, &ph_redir, ft_strlen(content_par->cmd_str) + 1);
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
		if (cmd[i] == '&') //TODO gestire il parse error in caso di piu' caratteri '&' di fila
			i++;
		while (cmd[i] && ft_isdigit(cmd[i]))
			i++;
	}
	if (is_shell_space(cmd[i]))
		*fd = ft_atoi(cmd + i * (flag == LEFT)); //TODO	gestire il caso di un FD che supera MAX INT (direttamente in atoi)
	else
		return (-1);
	return (0);
}

static void	add_left_right_filenames(char **filename, char *cmd, uint8_t flag, t_data *data)
{
	unsigned int	i;
	char			*tmp;
	char			*name;

	name = NULL;
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
		name = ft_strtrim(tmp, " \n\t");
		free(tmp);
		if (!name)
			ft_quit(16, "failed to allocate memory", data);
	}
	else if (flag == RIGHT) //TODO gestire il caso in cui c'e' un token tipo & prima del filename
	{
		i = 0;
		while (cmd[i] && is_shell_space(cmd[i]))
			i++;
		name = ft_strdup(&cmd[i]);
		if (!name)
			ft_quit(16, "failed to allocate memory", data);
		while (cmd[i] && !is_shell_space(cmd[i]))
			i++;
		name[i] = '\0';
	}
	free(*filename);
	*filename = name;
}
