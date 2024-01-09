/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/09 17:18:51 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token  lexer_get_token(char c);
static bool 	is_token(char *str);

//il lexer separa i token (> < e |) dal resto del comando ("ls -a -l ") che e' tutto insieme compresi spazi successivi
//dopo andra' fatto uno split/trim del comando prima di execve

//TODO capire come gestire double e single quote, valutare se e' meglio gestirle in lexer o parser

t_list	**lexer(char *input)
{
    unsigned int    i;
    t_lexer   		*content;
    t_list         	**lexered_params_head;

	lexered_params_head = (t_list **)malloc(sizeof(t_list *));
	if (!lexered_params_head)
		ft_quit(9, "failed to allocate memory");
	*lexered_params_head = NULL;
    while (*input != '\0')
    {
        i = 0;
        while (input[i] && !is_token(input + i))
            i++;
        if (i > 0)
        {
			content = (t_lexer *)malloc(sizeof(t_lexer));
            if (!content)
                ft_quit(7, "failed to allocate memory");
			content->type = CMD;
			content->str.cmd = (char *)malloc(sizeof(char) * i + 1);
			if (!content->str.cmd)
				ft_quit(8, "failed to allocate memory");
            ft_strlcpy(content->str.cmd, input, i + 1);
			ft_lstadd_back(lexered_params_head, ft_lstnew(content));
            input += i;
            i = 0;
        }
		if (*input != '\0')
		{
			content = (t_lexer *)malloc(sizeof(t_lexer));
			content->type = TOKEN;
       	 	content->str.token = lexer_get_token(*input++);
			ft_lstadd_back(lexered_params_head, ft_lstnew(content));
		}
    }
	return (lexered_params_head);
}

static t_token lexer_get_token(char c)
{
    int8_t         	i;
	static uint8_t	n_tokens;
    static int		tokens[4][2] = {
    {'|', PIPE},
    {'>', REDIR_R},
    {'<', REDIR_L},
	{'$', ENV},
    };

	n_tokens = sizeof(tokens) / sizeof(tokens[0]);
    i = -1;
    while (++i < (n_tokens))
        if (tokens[i][0] == c)
            return (tokens[i][1]);
    return (0);
}

static bool is_token(char *str)
{
    int8_t			i;
	static uint8_t	n_tokens;
    static char		tokens[4] = 
    {'|', '>', '<', '$'};

	n_tokens = sizeof(tokens) / sizeof(tokens[0]);
	i = -1;
   	while (++i < n_tokens)
	{
		if (tokens[i] == *str)
			return (true);
	}
	return (false);
}
