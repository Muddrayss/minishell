/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/01/13 14:58:54 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdint.h>
# include <stdbool.h>

typedef enum e_token
{
    PIPE,
    REDIR_R,
    REDIR_L,
    ENV,
}           t_token;

typedef enum e_elem_type
{
    CMD,
    TOKEN,
}           t_elem_type;

typedef struct s_lexer
{
    t_elem_type type;
    union u_elem
    {
        char    *cmd;
        t_token token;
    }           str;
}               t_lexer;

t_list		*lexer(char *input, t_data *data);

#endif