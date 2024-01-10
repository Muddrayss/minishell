/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/01/10 13:17:09 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define LEFT  0
# define RIGHT 1

typedef enum e_redirection_type
{
    REDIR_INPUT,                // 'filename <'
    REDIR_HEREDOC,              // '<< limiter'
    REDIR_INPUT_FD,             // '<&n'
    REDIR_OUTPUT,               // '> filename'
    REDIR_OUTPUT_FD,            // '>&n'
    REDIR_FD_DUP,               // 'n>&n'
    REDIR_OUTPUT_DUP,           // 'n>'
    REDIR_APPEND,               // '>> filename'
    REDIR_APPEND_FD,            // '>>&n'
}	t_redirection_type;

typedef struct s_redirection
{
    t_redirection_type	type;
    union u_input
    {
        int     fd;
        char    *filename; //o limiter in caso dell heredoc
    }                   input;
    union u_output
    {
        int     fd;
        char    *filename;
    }                   output;
}	t_redir;

//TODO aggiungere un placeholder in cmd_args per ricordarsi a che punto eseguire una redirection

typedef struct s_parser
{
    char	*cmd_str;
	t_list	**redirections;
}	t_parser;

#endif
