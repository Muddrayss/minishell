/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 22:32:25 by craimond         ###   ########.fr       */
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
	char	*cmd_str;
	t_list	*redirs;
}t_cmd;

// typedef struct s_tree
// {
// 	int8_t			type;
// 	t_cmd			*cmd;
// 	struct s_tree 	*left;
// 	struct s_tree	*right;
// }t_tree;

typedef struct s_parser
{
	int8_t	type;
	t_cmd	*cmd;
}t_parser;

typedef struct s_redir
{
	int8_t		type;
	char 		*filename; // o limiter in caso dell heredoc
	int32_t		heredoc_fileno; //eventuale numero da appendere al nome del heredoc
}t_redir;

t_tree	*parser(t_list *lexered_params);
void	merge_separators(t_list **lexered_params);
int8_t  check_syntax(t_list *lexered_params);
t_list  *fill_redirs(char *cmd_str);
char    *clear_redirs(char *cmd_str);
bool    is_empty_cmd(void *content);
void    del_content_parser(void *content);
void    del_content_redirs(void *content);

#endif
