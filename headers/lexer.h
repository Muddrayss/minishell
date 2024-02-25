/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/02/25 16:01:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer
{
	char	*cmd_str;
	bool    *dollar_array;
    bool    *redirs_array;
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