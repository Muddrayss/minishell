/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 19:43:27 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define PIPE 			'|'
# define REDIR_R 		'>'
# define REDIR_L 		'<'
# define SEMICOLON 		';'
# define QUOTE 			'\''
# define DQUOTE 		'"'
# define AMPERSAND 		'&'
# define PARENTHESIS_L 	'('
# define PARENTHESIS_R	')'

typedef struct s_lexer
{
	char	*cmd_str;
	char	token;
}t_lexer;

typedef struct s_list
{
    void			*content;
    struct s_list	*next;
    struct s_list	*prev;
}t_list;

t_list	*lexer(char *input);
void	del_content_lexer(void *content);

#endif