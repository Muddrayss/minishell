/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/06 17:55:44 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token  lexer_get_token(char c);
static bool is_token(char c);

//il lexer separa i token (> < e |) dal resto del comando ("ls -a -l ") che e' tutto insieme compresi spazi successivi
//dopo andra' fatto uno split/trim del comando prima di execve

//TODO capire come gestire double e single quote, valutare se e' meglio gestirle in lexer o parser

t_list	**lexer(char *input)
{
    unsigned int    i;
    union u_elem   	*elem;
    t_list         	**lexered_params_head;

	lexered_params_head = (t_list **)malloc(sizeof(t_list *));
	if (!lexered_params_head)
		ft_quit(9, "failed to allocate memory");
	lexered_params_head = NULL;
    while (*input != '\0')
    {
        i = 0;
        while (input[i] && !is_token(input[i]))
            i++;
        if (i > 0)
        {
			elem = (union u_elem *)malloc(sizeof(union u_elem));
            if (!elem)
                ft_quit(7, "failed to allocate memory");
			elem->cmd = (char *)malloc(sizeof(char) * i + 1);
			if (!elem->cmd)
				ft_quit(8, "failed to allocate memory");
            ft_strlcpy(elem->cmd, input, i + 1);
			ft_lstadd_back(lexered_params_head, ft_lstnew(elem));
            input += i;
            i = 0;
        }
        elem->token = lexer_get_token(*input++);
		ft_lstadd_back(lexered_params_head, ft_lstnew(elem));
    }
	return (lexer);
}

static t_token lexer_get_token(char c)
{
    uint8_t         i;
    static t_token  tokens[4][2] = {
    {'|', PIPE},
    {'>', REDIR_R},
    {'<', REDIR_L},
	{'$', ENV},
    };

    i = -1;
    while (++i < (sizeof(tokens) / sizeof(tokens[0])))
        if (tokens[i][0] == c)
            return (tokens[i][1]);
    return (0);
}

static bool is_token(char c)
{
    uint8_t		i;
    static char	tokens[3] = 
    {'|', '>', '<'};

	i = 0;
    while (i < 3)
		if (tokens[i++] == c)
			return (true);
	return (false);
}
