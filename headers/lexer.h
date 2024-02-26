/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/02/26 18:04:39 by craimond         ###   ########.fr       */
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

typedef struct s_list
{
    void			*content;
    struct s_list	*next;
    struct s_list	*prev;
}t_list;

static const char   g_ph_redirl
    = -'<';
static const char   g_ph_redirr
    = -'>';
static const char   g_ph_asterisk
    = -'*';
static const char   g_tokens[7]
    = {'|', ';', '&', '(', ')'};

t_list	*lexer(char *input);
char    *expand(char *str);
char    *replace_env_vars(char *cmd_str);
char    *replace_wildcards(char *cmd_str);
void	del_content_lexer(void *content);

#endif
