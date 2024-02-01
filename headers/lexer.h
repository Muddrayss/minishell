/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/02/01 13:39:12 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdint.h>

# define PIPE '|'
# define REDIR_R '>'
# define REDIR_L '<'
# define SEMICOLON ';'
# define QUOTE '\''
# define DQUOTE '"'
# define AND '&'
# define PARENTHESIS_L '('
# define PARENTHESIS_R ')'

typedef struct s_lexer
{
	char	*cmd;
	char	token;
}				t_lexer;

t_list			*lexer(char *input);
void			del_content_lexer(void *content);

#endif