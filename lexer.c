/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/06 13:03:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token  lexer_get_token(char c);

void    lexer(char *input)
{
    unsigned int    i;
    char            *cmd;
    t_lexer         *lexer;

    while (*input != '\0')
    {
        i = 0;
        while (input[i] && !is_token(input[i]))
            i++;
        if (i > 0)
        {
            lexer = (t_lexer *)malloc(sizeof(t_lexer));
            lexer->cmd = (char *)malloc(sizeof(char) * i + 1);
            if (!lexer->cmd)
                ft_quit(7, "failed to allocate memory");
            ft_strlcpy(lexer->cmd, input, i + 1);
            lexer = lexer->next;
            input += i;
            i = 0;
        }
        lexer = (t_lexer *)malloc(sizeof(t_lexer));
        lexer->token = lexer_get_token(*input++);
        lexer = lexer->next;
    }
}

static t_token lexer_get_token(char c)
{
    uint8_t         i;
    static t_token  tokens[3][2] = {
    {'|', PIPE},
    {'>', REDIR_R},
    {'<', REDIR_L},
    };

    i = -1;
    while (++i < 3)
        if (tokens[i][0] == c)
            return (tokens[i][1]);
    return (0);
}
