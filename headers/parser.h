/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 14:25:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define END 			   -1
# define CMD 				0 //CMD deve essere zero, altrimenti non funziona treenew con il token
# define SEMICOLON			1
# define OR 				2
# define AND 				3
# define PIPELINE 			4
# define SUBSHELL_START 	5
# define SUBSHELL_END 		6

# define REDIR_INPUT 		0 	// < filename
# define REDIR_HEREDOC 		1	// << limiter
# define REDIR_OUTPUT 		2 	// > filename
# define REDIR_APPEND 		3 	// >> filename

static const char g_parser_tokens[7]
= {'\0', ';', '|', '&', '|', '(', ')'};

# define BEFORE 0
# define AFTER  1

typedef struct s_command
{
	t_list	*redirs;
	char	*cmd_str;
}t_cmd;

typedef struct s_parser
{
	t_cmd	*cmd;
	int8_t	type;
}t_parser;

typedef struct s_redir
{
	char 		*filename; // o limiter in caso dell heredoc
	int16_t		heredoc_fileno; //eventuale numero da appendere al nome del heredoc
	int8_t		type;
}t_redir;

void	parser(t_list *lexered_params);
int8_t 	merge_separators(t_list **const lexered_params);
int8_t 	check_syntax(const t_list *const lexered_params);
void	throw_syntax_error(const char token);
t_list  *fill_redirs(const char *const cmd_str);
char    *clear_redirs(const char *cmd_str);
bool    is_empty_cmd(const void *const content);
bool 	is_redir(const char c);
void    del_content_parser(const void *const content);
void    del_content_redirs(const void *const content);

#endif
