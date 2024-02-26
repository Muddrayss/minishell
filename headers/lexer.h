/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/02/26 02:51:56 by craimond         ###   ########.fr       */
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

#define N_PLACEHOLDERS 5

static const char g_ph_asterisk = -1;
static const char g_ph_dollar = -2;
static const char g_ph_redirl = -3;
static const char g_ph_redirr = -4;

static const char   g_tokens[7]
    = {'|', ';', '&', '(', ')'};

t_list	*lexer(char *input);
void	del_content_lexer(void *content);
char    *replace_env_vars(char *cmd_str);
char    *replace_wildcards(char *cmd_str);

#endif