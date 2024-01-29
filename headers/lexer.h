/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/01/29 17:40:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdint.h>

typedef enum e_token
{
	EMPTY = -1,
	PIPE,
	REDIR_R,
	REDIR_L,
	SLASH,
	SEMICOLON,
	QUOTE,
	DQUOTE,
	AND
}				t_token;

typedef enum e_elem_type
{
	CMD,
	TOKEN,
}				t_elem_type;

typedef struct s_lexer
{
	t_elem_type	type;
	union		u_elem
	{
		char	*cmd;
		t_token	token;
	} str;
}				t_lexer;

t_list			*lexer(char *input);
void			del_content_lexer(void *content);

#endif