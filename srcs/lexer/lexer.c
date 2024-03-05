/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:13:01 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 00:06:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	add_cmd_and_token(t_list **const lexered_params, const char *const input, const uint16_t i);
static void	lexer_add_cmd(t_list **const lexered_params, const uint16_t cmd_len, const char *const input);
static void	lexer_add_token(t_list **const lexered_params, const char c);
static bool	is_token(const char c);

t_list	*lexer(const char *input)
{
	uint16_t	i;
	char		master_quote;
	t_list		*lexered_params;

	lexered_params = NULL;
	master_quote = '\0';
	i = -1;
	while (input[++i])
	{
		if (is_quote(input[i]))
		{
			if (!master_quote)
				master_quote = input[i];
			else if (master_quote == input[i])
				master_quote = '\0';
		}
		else if (!master_quote && is_token(input[i]))
		{
			add_cmd_and_token(&lexered_params, input, i);
			input += i + 1;
			i = -1;
		}
	}
	add_cmd_and_token(&lexered_params, input, i);
	lstreverse(&lexered_params);
	return (lexered_params);
}

static void	add_cmd_and_token(t_list **const lexered_params, const char *const input, const uint16_t i)
{
	if (i > 0)
		lexer_add_cmd(lexered_params, i, input);
	if (input[i])
		lexer_add_token(lexered_params, input[i]);
}

static void	lexer_add_cmd(t_list **const lexered_params, const uint16_t cmd_len, const char *const input)
{
	t_lexer	*content;

	content = (t_lexer *)malloc_p(sizeof(t_lexer));
	content->token = 0;
	content->cmd_str = (char *)malloc_p(sizeof(char) * (cmd_len + 1));
	ft_strlcpy(content->cmd_str, input, cmd_len + 1);
	lstadd_front(lexered_params, lstnew(content, false));
}

static void	lexer_add_token(t_list **const lexered_params, const char c)
{
	t_lexer	*content;

	content = (t_lexer *)malloc_p(sizeof(t_lexer));
	content->token = c;
	content->cmd_str = NULL;
	lstadd_front(lexered_params, lstnew(content, false));
}

static bool	is_token(const char c)
{
	return (ft_strchr(g_lexer_tokens, c) != NULL);
}
