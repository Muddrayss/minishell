/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/02/27 18:19:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool 	is_token(char c);
static void 	lexer_add_cmd(t_list **lexered_params, uint32_t cmd_len, char *input);
static void 	lexer_add_token(t_list **lexered_params, char c);

t_list	*lexer(char *input)
{
    uint32_t        cmd_len;
    char            *cmd_str;
    char            current_quote;
    t_list         	**lexered_params;

	lexered_params = (t_list **)malloc_p(sizeof(t_list *));
    *lexered_params = NULL;
    current_quote = '\0';
    get_data()->lexered_params = lexered_params;
    cmd_len = 0;
    while (true)
    {
        if (is_quote(*input))
        {
            if (!current_quote)
                current_quote = *input;
            else if (current_quote == *input)
                current_quote = '\0';
        }
        else if (!current_quote && (is_token(*input) || *input == '\0'))
        {
            cmd_str = (char *)malloc_p(sizeof(char) * (cmd_len + 1));
            ft_strlcpy(cmd_str, input - cmd_len, cmd_len + 1);
            lexer_add_cmd(lexered_params, cmd_len, cmd_str);
            lexer_add_token(lexered_params, *input);
            cmd_len = -1;
        }
        cmd_len++;
        if (!*input)
            break ;
        input++;
    }
    return (lstreverse(lexered_params), *lexered_params);
}

static void lexer_add_cmd(t_list **lexered_params, uint32_t cmd_len, char *cmd_str_raw)
{
    t_lexer   		*content;
    
    if (cmd_len <= 0)
        return ;
    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->token = 0;
    content->cmd_str = cmd_str_raw;
    lstadd_front(lexered_params, lstnew_p(content));
}

static void lexer_add_token(t_list **lexered_params, char c)
{
    t_lexer   		*content;

    if (!c)
        return ;
    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->token = c;
    content->cmd_str = NULL;
    lstadd_front(lexered_params, lstnew_p(content));
}

static bool is_token(char c)
{
    int8_t			        i;
	static const uint8_t	n_tokens = sizeof(g_tokens) / sizeof(g_tokens[0]);

	i = -1;
   	while (++i < n_tokens)
		if (g_tokens[i] == c)
			return (true);
	return (false);
}

void	del_content_lexer(void *content)
{
	t_lexer	*elem;

	elem = (t_lexer *)content;
	free(elem->cmd_str);
    free(elem);
}
