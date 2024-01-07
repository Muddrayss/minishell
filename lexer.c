/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/07 16:42:45 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token  lexer_get_token(char c);
static bool 	is_token(char *str, bool is_first);
static bool		is_num_before(char *str);

//il lexer separa i token (> < e |) dal resto del comando ("ls -a -l ") che e' tutto insieme compresi spazi successivi
//dopo andra' fatto uno split/trim del comando prima di execve

//TODO capire come gestire double e single quote, valutare se e' meglio gestirle in lexer o parser

t_list	**lexer(char *input)
{
    unsigned int    i;
	bool			is_first;
    t_lexer   		*elem;
    t_list         	**lexered_params_head;

	lexered_params_head = (t_list **)malloc(sizeof(t_list *));
	if (!lexered_params_head)
		ft_quit(9, "failed to allocate memory");
	lexered_params_head = NULL;
	is_first = true;
    while (*input != '\0')
    {
        i = 0;
        while (input[i] && !is_token(input + i, is_first))
            i++;
        if (i > 0)
        {
			elem = (t_lexer *)malloc(sizeof(t_lexer));
            if (!elem)
                ft_quit(7, "failed to allocate memory");
			elem->type = CMD;
			elem->str.cmd = (char *)malloc(sizeof(char) * i + 1);
			if (!elem->str.cmd)
				ft_quit(8, "failed to allocate memory");
            ft_strlcpy(elem->str.cmd, input, i + 1);
			ft_lstadd_back(lexered_params_head, ft_lstnew(elem));
            input += i;
            i = 0;
        }
		elem = (t_lexer *)malloc(sizeof(t_lexer));
		elem->type = TOKEN;
        elem->str.token = lexer_get_token(*input++);
		ft_lstadd_back(lexered_params_head, ft_lstnew(elem));
		is_first = false;
    }
	return (lexered_params_head);
}

static t_token lexer_get_token(char c)
{
    int8_t         i;
	static uint8_t	n_tokens;
    static t_token  tokens[4][2] = {
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

static bool is_token(char *str, bool is_first)
{
    int8_t			i;
	bool			is_number_before;
	static uint8_t	n_tokens;
    static char		tokens[4] = 
    {'|', '>', '<', '$'};

	n_tokens = sizeof(tokens) / sizeof(tokens[0]);
	i = -1;
   	while (++i < n_tokens)
	{
		if (tokens[i] == *str)
		{
			//per evitare i casi tipo (cmd arg1>) e (> out)
			if (*str == '>' && !(is_first == true || is_shell_space(str[-1]) == true || is_num_before(str - 1) == true))
				return (false);
			return (true);
		}
	}
	return (false);
}

static bool	is_num_before(char *str)
{
	unsigned int	i;

	i = 0;
	while (*str >= '0' && *str <= '9')
	{
		str--;
		i++;
	}
	if (i > 0 && is_shell_space(*str) == true)
		return (true);
	return (false);
}
