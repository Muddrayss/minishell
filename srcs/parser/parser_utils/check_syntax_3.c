/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:02:13 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 16:04:08 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	handle_quote(char *master_quote, char c)
{
	if (is_quote(c))
	{
		if (*master_quote == '\0')
			*master_quote = c;
		else if (*master_quote == c)
			*master_quote = '\0';
	}
}

static int8_t	process_redirection_checks(const char *cmd_str, uint16_t *i)
{
	if (check_redir_streak(cmd_str + *i) == 1
		|| check_redir_pair(cmd_str + *i) == 1
		|| check_filename_presence(cmd_str + *i) == 1)
		return (tse(cmd_str[*i]), -1);
	return (0);
}

int8_t	check_redirs(const t_list *lexered_params)
{
	t_lexer		*elem;
	uint16_t	i;
	char		master_quote;

	master_quote = '\0';
	while (lexered_params)
	{
		elem = (t_lexer *)lexered_params->content;
		lexered_params = lexered_params->next;
		if (!elem->cmd_str)
			continue ;
		i = 0;
		while (elem->cmd_str[i])
		{
			handle_quote(&master_quote, elem->cmd_str[i]);
			if (!master_quote && is_redir(elem->cmd_str[i]))
			{
				if (process_redirection_checks(elem->cmd_str, &i) == -1)
					return (-1);
			}
			i++;
		}
	}
	return (0);
}
