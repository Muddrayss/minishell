/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 16:24:51 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define CMD 				0
# define SEMICOLON			';'
# define OR 				2
# define AND 				3
# define PIPELINE 			4
# define SUBSHELL_START 	5
# define SUBSHELL_END 		6

# define REDIR_INPUT 		0 	// '< filename'
# define REDIR_HEREDOC 		1	// '<< limiter'
# define REDIR_INPUT_FD 	2 	// '<&n'
# define REDIR_OUTPUT 		3 	// '> filename o n> filename'
# define REDIR_OUTPUT_FD 	4 	// '>&n'
# define REDIR_APPEND 		5 	// '>> filename o n>> filename'
# define REDIR_APPEND_FD 	6 	// '>>&n'

# define BEFORE 0
# define AFTER  1

typedef struct s_redir		t_redir;
typedef struct s_command	t_cmd;
typedef struct s_tree		t_tree;

typedef struct s_command
{
	char	*cmd_str;
	t_list	*redirs;
}t_cmd;

typedef struct s_tree
{
	int8_t		type;
	t_cmd		cmd;
	t_tree		*left;
	t_tree		*right;
}t_tree;

typedef struct s_redir
{
	int8_t		type;
	int			fds[2];
	char 		*filename; // o limiter in caso dell heredoc
}t_redir;

t_tree	*parser(t_list *params_head);

#endif
