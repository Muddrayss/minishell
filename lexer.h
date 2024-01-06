/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:57:09 by craimond          #+#    #+#             */
/*   Updated: 2024/01/06 22:21:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdint.h>
# include <stdbool.h>

# define PIPE       1
# define REDIR_R    2
# define REDIR_L    3
# define ENV		4

typedef int8_t t_token;

typedef struct s_lexer
{
    union u_elem
    {
        char    *cmd;
        t_token token;
    }           str;
}               t_lexer;

#endif