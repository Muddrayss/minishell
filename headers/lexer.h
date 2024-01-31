/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/01/31 22:11:04 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdint.h>

typedef enum e_token
{
	PIPE = '|',
	REDIR_R = '>',
	REDIR_L = '<',
	SEMICOLON = ';',
	QUOTE = '\'',
	DQUOTE = '"',
	AND = '&',
}				t_token;

typedef struct s_lexer
{
	char	*cmd;
	t_token	token;
}				t_lexer;

t_list			*lexer(char *input);
void			del_content_lexer(void *content);

#endif