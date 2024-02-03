/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 14:15:58 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char     lexer_get_token(char c);
static bool 	is_token(char *str, int idx);
static t_lexer  *new_content_lexer(void);

t_list	*lexer(char *input)
{
    t_data          *data;
    int             i;
    t_lexer   		*content;
    t_list         	*lexered_params;

    data = get_data();
	lexered_params = NULL;
    data->lexered_params = &lexered_params;
    content = new_content_lexer();
    //TODO gestire ' e "" qui. aggiungere alla cmd_str invece che a TOKEN (flag stop?)
    while (*input != '\0')
    {
        i = 0;
        while (input[i] && !is_token(input, i))
            i++;
        if (i > 0)
        {
			content->cmd_str = (char *)malloc_p(sizeof(char) * (i + 1));
            ft_strlcpy(content->cmd_str, input, i + 1);
			ft_lstadd_back(&lexered_params, ft_lstnew(content));
            content = new_content_lexer();
            input += i;
        }
		if (input[0] != '\0')
		{
       	 	content->token = lexer_get_token(*input++);
            ft_lstadd_back(&lexered_params, ft_lstnew(content));
            content = new_content_lexer();
        }
    }
	return (lexered_params);
}

static  t_lexer *new_content_lexer(void)
{
    t_lexer	*content;

    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->cmd_str = NULL;
    content->token = 0;
    return (content);
}

static char     lexer_get_token(char c)
{
    int8_t         	i;
	static uint8_t	n_tokens;
    static int8_t   tokens[5] = {PIPE, SEMICOLON, AND, PARENTHESIS_L, PARENTHESIS_R};
    
	n_tokens = sizeof(tokens) / sizeof(tokens[0]);
    i = -1;
    while (++i < (n_tokens))
        if (tokens[i] == c)
            return (tokens[i]);
    return (0);
}

static bool is_token(char *str, int idx)
{
    int8_t			i;
	static uint8_t	n_tokens;
    static char     tokens[5] = {PIPE, SEMICOLON, AND, PARENTHESIS_L, PARENTHESIS_R};

    n_tokens = sizeof(tokens) / sizeof(tokens[0]);
	i = -1;
   	while (++i < n_tokens)
		if (tokens[i] == str[idx])
			return (true);
	return (false);
}

void	del_content_lexer(void *content)
{
	t_lexer	*elem;

	elem = (t_lexer *)content;
	free(elem->cmd_str);
}
