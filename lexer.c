/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/25 18:02:33 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static t_token  lexer_get_token(char c);
static bool 	is_token(char *str);

t_list	*lexer(char *input, t_data *data)
{
    unsigned int    i;
    t_lexer   		*content;
    t_list         	*lexered_params;

	lexered_params = NULL;
    data->lexered_params = &lexered_params;
    while (*input != '\0')
    {
        i = 0;
        while (input[i] && !is_token(input + i))
            i++;
        if (i > 0)
        {
			content = (t_lexer *)malloc(sizeof(t_lexer));
            if (!content)
                ft_quit(7, "failed to allocate memory", data);
			content->type = CMD;
			content->str.cmd = (char *)malloc(sizeof(char) * (i + 1));
			if (!content->str.cmd)
				ft_quit(8, "failed to allocate memory", data);
            ft_strlcpy(content->str.cmd, input, i + 1);
			ft_lstadd_back(&lexered_params, ft_lstnew(content));
            input += i;
            i = 0;
        }
		if (*input != '\0')
		{
			content = (t_lexer *)malloc(sizeof(t_lexer));
            if (!content)
                ft_quit(10, "failed to allocate memory", data);
			content->type = TOKEN;
       	 	content->str.token = lexer_get_token(*input++);
			ft_lstadd_back(&lexered_params, ft_lstnew(content));
		}
    }
	return (lexered_params);
}

static t_token lexer_get_token(char c)
{
    int8_t         	i;
	static uint8_t	n_tokens;
    static int tokens[9][2] = {
        {'|', PIPE},
        {'>', REDIR_R},
        {'<', REDIR_L},
        {'$', ENV},
        {'/', SLASH},
        {';', SEMICOLON},
        {'\'', QUOTE},
        {'\"', DQUOTE},
        {'&', AND}
    };

	n_tokens = sizeof(tokens) / sizeof(tokens[0]);
    i = -1;
    while (++i < (n_tokens))
        if (tokens[i][0] == c)
            return (tokens[i][1]);
    return (EMPTY);
}

static bool is_token(char *str)
{
    int8_t			i;
	static uint8_t	n_tokens;
    static char		tokens[9] = 
    {'|', '>', '<', '$', '/', ';', '\'', '\"', '&'};

	n_tokens = sizeof(tokens) / sizeof(tokens[0]);
	i = -1;
   	while (++i < n_tokens)
	{
		if (tokens[i] == *str)
			return (true);
	}
	return (false);
}

void	del_content_lexer(void *content)
{
	t_lexer	*elem;

	elem = (t_lexer *)content;
	if (elem->type == CMD)
		free(elem->str.cmd);
	free(elem);
}
