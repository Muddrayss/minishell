/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 23:19:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer
{
	char	*cmd_str;
    char	token;
	bool    is_literal;
}t_lexer;

static const char   g_tokens[7]
    = {'|', ';', '&', '(', ')'};

t_list	*lexer(char *input);
bool	is_token(char c);
void	del_content_lexer(void *content);

#endif
