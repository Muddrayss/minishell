/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:45 by craimond          #+#    #+#             */
/*   Updated: 2024/01/12 19:57:44 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	check_token_streak(t_token *next_token, t_list *lexered_params)
{
	unsigned int	token_streak;
	t_list			*tmp;

	token_streak = 0;
	tmp = lexered_params;
	while (((t_lexer *)tmp->content)->type == TOKEN && ((t_lexer *)tmp->content)->str.token != PIPE)
	{
		token_streak++;
		tmp = tmp->next;
	}
	*next_token = ((t_lexer *)lexered_params->next->content)->str.token;
	return (token_streak);
}

t_parser	*new_elem(size_t *size, t_list *lexered_params, t_data *data)
{
	t_parser 		*elem;
	unsigned int	num_env;

	elem = (t_parser *)malloc(sizeof(t_parser));
	if (!elem)
		ft_quit(10, "failed to allocate memory", data);
	elem->cmd_str = NULL;
	elem->redirs = NULL;
	*size = get_len_between_pipes(lexered_params) + 1;
	num_env = get_env_num_between_pipes(lexered_params->next);
	elem->cmd_str = (char *)malloc(sizeof(char) * *size);
	if (!elem->cmd_str)
	{
		free(elem);
		ft_quit(12, "failed to allocate memory", data);
	}
	elem->env_vars = (char **)malloc(sizeof(char *) * num_env + 1);
	if (!elem->env_vars && num_env > 0)
	{
		free(elem->cmd_str);
		free(elem);
		ft_quit(13, "failed to allocate memory", data);
	}
	elem->env_vars[num_env] = NULL;
}

unsigned int	get_len_between_pipes(t_list *lexered_params)
{
	unsigned int	cmd_len;
	t_lexer			l_content;

	cmd_len = 0;
	l_content = *((t_lexer *)lexered_params->content);
	while (lexered_params)
	{
		l_content = *((t_lexer *)lexered_params->content);
		if (l_content.type == CMD)
			cmd_len += ft_strlen(l_content.str.cmd) + 1; //per eventuali token
		lexered_params = lexered_params->next;
	}
}

void	remove_word(char **str, unsigned int starting_idx, uint8_t flag, t_data *data)
{
	unsigned int	i;
	unsigned int	j;
	char			*new_str;

	i = starting_idx;
	j = ft_strlen(&(*str)[starting_idx]);
	if (flag == LEFT)
	{
		while (is_shell_space((*str)[i]))
			i--;
		while ((*str)[i] > 0 && !is_shell_space((*str)[i]))
			i--;
		new_str = (char *)ft_calloc(i + j + 1, sizeof(char));
		if (!new_str)
			ft_quit(15, "failed to allocate memory", data);
		ft_strlcat(new_str, *str, i + 1);
		ft_strlcat(new_str, *str + starting_idx, j + 1);
	}
	else
	{
		while (is_shell_space((*str)[i]))
			i++;
		while ((*str)[i] > 0 && !is_shell_space((*str)[i]))
			i++;
		new_str = (char *)ft_calloc(starting_idx + (j - i) + 1, sizeof(char));
		if (!new_str)
			ft_quit(15, "failed to allocate memory", data);
		ft_strlcat(new_str, *str, starting_idx + 1);
		ft_strlcat(new_str, *str + i, j - i + 1);
	}
	free(*str);
	*str = new_str;
}

void	remove_num(char **str, unsigned int starting_idx, uint8_t flag, t_data *data)
{
	unsigned int	i;
	unsigned int	j;
	char			*new_str;

	i = starting_idx;
	j = ft_strlen(&(*str)[starting_idx]);
	if (flag == LEFT)
	{
		while ((*str)[i] > 0 && ft_isdigit((*str)[i]))
			i--;
		new_str = (char *)ft_calloc(i + j + 1, sizeof(char));
		if (!new_str)
			ft_quit(15, "failed to allocate memory", data);
		ft_strlcat(new_str, *str, i + 1);
		ft_strlcat(new_str, *str + starting_idx, j + 1);
	}
	else
	{
		if ((*str)[i] == '&')
			i++;
		while ((*str)[i] > 0 && ft_isdigit((*str)[i]))
			i++;
		new_str = (char *)ft_calloc(starting_idx + (j - i) + 1, sizeof(char));
		if (!new_str)
			ft_quit(15, "failed to allocate memory", data);
		ft_strlcat(new_str, *str, starting_idx + 1);
		ft_strlcat(new_str, *str + i, j - i + 1);
	}
	free(*str);
	*str = new_str;
}