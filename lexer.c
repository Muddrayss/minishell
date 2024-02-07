/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/02/07 15:45:01 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static bool 	is_token(char c);
static void 	lexer_add_cmd(t_list **lexered_params, uint32_t cmd_len, char *input);
static void 	lexer_add_token(t_list **lexered_params, char c);

t_list	*lexer(char *input)
{
    uint32_t        cmd_len;
    t_list         	*lexered_params;

	lexered_params = NULL;
    get_data()->lexered_params = &lexered_params;
    //TODO gestire ' e "" qui. aggiungere alla cmd_str invece che a TOKEN (flag stop?)
    while (*input != '\0')
    {
        cmd_len = 0;
        while (input[cmd_len] && !is_token(input[cmd_len]))
            cmd_len++;
        if (cmd_len > 0)
            lexer_add_cmd(&lexered_params, cmd_len, input);
        input += cmd_len;
		if (input[0] != '\0')
            lexer_add_token(&lexered_params, *input++);
    }
    lstreverse(&lexered_params); //per mettere la testa al posto giusto (la lista era stata riempita al contrario)
	return (lexered_params);
}

static void lexer_add_cmd(t_list **lexered_params,uint32_t cmd_len, char *input)
{
    t_lexer   		*content;

    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->cmd_str = (char *)malloc_p(sizeof(char) * (cmd_len + 1));
    content->token = 0;
    ft_strlcpy(content->cmd_str, input, cmd_len + 1);
    lstadd_front(lexered_params, lstnew_p(content));
}

static void lexer_add_token(t_list **lexered_params, char c)
{
    t_lexer   		*content;

    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->token = c;
    content->cmd_str = NULL;
    lstadd_front(lexered_params, lstnew_p(content));
}

static bool is_token(char c)
{
    int8_t			i;
    static char     tokens[5] = {'|', ';', '&', '(', ')'};
	static uint8_t	n_tokens = sizeof(tokens) / sizeof(tokens[0]);

	i = -1;
   	while (++i < n_tokens)
		if (tokens[i] == c)
			return (true);
	return (false);
}

void	del_content_lexer(void *content)
{
	t_lexer	*elem;

	elem = (t_lexer *)content;
	free(elem->cmd_str);
}
