/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:45 by craimond          #+#    #+#             */
/*   Updated: 2024/01/29 19:43:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static unsigned int	get_x_between_pipes(t_list *lexered_params, uint8_t flag);

unsigned int	check_token_streak(t_token *next_token, t_list *lexered_params)
{
	unsigned int	token_streak;
	t_lexer			*elem;
	t_list			*tmp;

	token_streak = 0;
	tmp = lexered_params;
	while (tmp)
	{
		elem = (t_lexer *)tmp->content;
		if (elem->type == TOKEN)
			token_streak++;
		else
			break ;
		tmp = tmp->next;
	}
	if (next_token && token_streak > 1)
		*next_token = ((t_lexer *)lexered_params->next->content)->str.token;
	else if (next_token)
		*next_token = EMPTY;
	return (token_streak);
}

t_parser	*new_elem(size_t *size, t_list *lexered_params)
{
	t_parser		*elem;

	elem = (t_parser *)malloc(sizeof(t_parser));
	if (!elem)
		ft_quit(10, "failed to allocate memory");
	elem->redirs = NULL;
	elem->pid = -1;
	*size = get_x_between_pipes(lexered_params, CMD_LEN) + 2;
	elem->cmd_str = (char *)ft_calloc(*size, sizeof(char));
	if (!elem->cmd_str)
	{
		free(elem);
		ft_quit(12, "failed to allocate memory");
	}
	return (elem);
}

static unsigned int	get_x_between_pipes(t_list *lexered_params, uint8_t flag)
{
	unsigned int	n;
	t_lexer			l_content;

	n = 0;
	while (lexered_params)
	{
		l_content = *((t_lexer *)lexered_params->content);
		if (flag == CMD_LEN && l_content.type == CMD)
			n += ft_strlen(l_content.str.cmd) + 1; // per eventuali token
		else if (l_content.type == TOKEN && l_content.str.token == PIPE)
			break ;
		lexered_params = lexered_params->next;
	}
	return (n);
}

void	remove_filename(char **str, unsigned int *starting_idx)
{
	unsigned int	word_len;
	unsigned int	i;

	word_len = 0;
	i = *starting_idx + 1;
	while (is_shell_space((*str)[i]))
		i++;
	while ((*str)[i + word_len] != '\0' && !is_shell_space((*str)[i + word_len]))
		word_len++;
	*str = ft_insert_str(*str, " ", *starting_idx, i + word_len);
	*starting_idx += word_len;
}

void	remove_num(char **str, unsigned int *starting_idx, uint8_t flag)
{
	unsigned int	i;
	unsigned int	j;
	size_t			size;
	char			*new_str;

	i = *starting_idx - (flag == LEFT) + (flag == RIGHT);
	j = ft_strlen(&(*str)[*starting_idx]) + 1;
	if (flag == LEFT)
	{
		while ((*str)[i] != '\0' && ft_isdigit((*str)[i]))
			i--;
		size = i + j + 1;
		new_str = (char *)ft_calloc(size, sizeof(char)); // ls 1> fsdds
		if (!new_str)
			ft_quit(15, "failed to allocate memory");
		ft_strlcpy(new_str, *str, i + 2);
		ft_strlcat(new_str, *str + *starting_idx, size);
		*starting_idx = i + 1;
	}
	else
	{
		if ((*str)[i] == '&')
			i++;
		while ((*str)[i] != 0 && ft_isdigit((*str)[i]))
			i++;
		size = *starting_idx + (j - i) + 1;
		new_str = (char *)ft_calloc(size, sizeof(char));
		if (!new_str)
			ft_quit(15, "failed to allocate memory");
		ft_strlcpy(new_str, *str, *starting_idx + 2);
		ft_strlcat(new_str, *str + i, size);
	}
	free(*str);
	*str = new_str;
}

t_lexer	*get_next_cmd_elem(t_list *lexered_params)
{
	t_lexer	*elem;

	while (lexered_params)
	{
		elem = (t_lexer *)lexered_params->content;
		if (elem->type == CMD)
			return (elem);
		lexered_params = lexered_params->next;
	}
	return (NULL);
}

bool	is_empty_cmd(void *content)
{
	t_lexer	*elem;
	char	*tmp;

	elem = (t_lexer *)content;
	if (elem->type == CMD)
	{
		tmp = ft_strtrim(elem->str.cmd, " \t\n");
		if (!tmp)
			ft_quit(15, "failed to allocate memory");
		if (*tmp == '\0')
		{
			free(tmp);
			return (true);
		}
		free(tmp);
	}
	return (false);
}

void	del_content_parser(void *content)
{
	t_parser	*elem;

	elem = (t_parser *)content;
	free(elem->cmd_str);
	ft_lstclear(&elem->redirs, &del_content_redirs);
	free(elem);
}

void	del_content_redirs(void *content)
{
	t_redir *elem;

	elem = (t_redir *)content;
	if (elem->filename)
		free(elem->filename);
}