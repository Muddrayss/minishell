/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:45 by craimond          #+#    #+#             */
/*   Updated: 2024/01/13 19:44:57 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	get_x_between_pipes(t_list *lexered_params, uint8_t flag);

unsigned int	check_token_streak(t_token *next_token, t_list *lexered_params)
{
	unsigned int	token_streak;
	t_lexer			*elem;
	t_list			*tmp;
	char			*str;

	token_streak = 0;
	tmp = lexered_params;
	while (tmp)
	{
		elem = (t_lexer *)tmp->content;
		if (elem->type != TOKEN)
		{
			str = ft_strtrim(elem->str.cmd, " \t\n");
			if (str[0] != '\0')
			{
				free(str);
				break ;
			}
			free(str);
		}
		token_streak++;
		tmp = tmp->next;
	}
	if (next_token)
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
	*size = get_x_between_pipes(lexered_params, CMD_LEN) + 1;
	num_env = get_x_between_pipes(lexered_params->next, ENV_NUM);
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
			n += ft_strlen(l_content.str.cmd) + 1; //per eventuali token
		else if (flag == ENV_NUM && l_content.type == TOKEN && l_content.str.token == ENV)
			n++;
		else if (l_content.type == TOKEN && l_content.str.token == PIPE)
			break ;
		lexered_params = lexered_params->next;
	}
	return (n);
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

void	replace_env_var(char **str, unsigned int starting_idx, char *env_var, t_data *data)
{
	char				*new_str;
	unsigned int		i;
	unsigned int		j;
	unsigned int		env_var_len;
	static const char	ph_invalid_env
		= -44;

	env_var_len = ft_strlen(env_var);
	j = ft_strlen(&(*str)[starting_idx]);
	i = 0;
	while ((*str)[i] > 0 && !is_shell_space((*str)[i]))
		i++;
	new_str = (char *)ft_calloc(starting_idx + (j - i) + env_var_len + 1, sizeof(char));
	if (!new_str)
		ft_quit(15, "failed to allocate memory", data);
	ft_strlcat(new_str, *str, starting_idx + 1);
	if (env_var)
		ft_strlcat(new_str, env_var, env_var_len + 1);
	else
		ft_strlcat(new_str, &ph_invalid_env, 2); //per evitare casi come echo hello > $dvuawku
	ft_strlcat(new_str, *str + i, j - i + 1);
	free(*str);
	*str = new_str;
}