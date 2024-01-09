/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/01/09 19:51:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_redirection_type
{
    REDIR_INPUT,                // '<'
    REDIR_OUTPUT,               // '>'
    REDIR_APPEND,               // '>>'
    REDIR_HEREDOC,              // '<<'
    REDIR_INPUT_FD,             // '<&n'
    REDIR_OUTPUT_FD,            // '>&n'
    REDIR_READ_WRITE,           // '<>'
    REDIR_READ_WRITE_FD,         // 'n<>'
    REDIR_FD_DUP_AND_CLOSE,     // 'n>&n'
    REDIR_FD_DUP,               // 'n>&m-'
    REDIR_APPEND_FD,            // '>>&n'
    REDIR_INPUT_DUP,            // 'n<'
    REDIR_OUTPUT_DUP,           // 'n>'
    REDIR_CLOSE_FD              // 'n<&-'
}	t_redirection_type;

typedef struct s_vars
{
	char			*name;
	char			*value; //con getenv(name);
	struct s_vars	*next;
}	t_vars;

typedef struct s_redirection
{
    t_redirection_type	type;
    int                 fds[2];
}	t_redir;

//TODO aggiungere un placeholder in cmd_args per ricordarsi a che punto eseguire una redirection

typedef struct s_parser
{
    char	*cmd_str;
	t_list	**redirections;
}	t_parser;

#endif