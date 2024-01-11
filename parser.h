/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/01/11 14:58:13 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define LEFT  0
# define RIGHT 1

typedef enum e_redir_type
{
    REDIR_INPUT,                // 'filename <'
    REDIR_HEREDOC,              // '<< limiter'
    REDIR_INPUT_FD,             // '<&n'
    REDIR_OUTPUT,               // '> filename o n> filename'
    REDIR_OUTPUT_FD,            // '>&n'
    REDIR_APPEND,               // '>> filename o n>> filename'
    REDIR_APPEND_FD,            // '>>&n'
}	t_redir_type;

typedef struct s_redir
{
    t_redir_type	type;
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
    char    **env_vars;
}	t_parser;

void	        handle_redir_l(t_list *lexered_params, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data);
void	        handle_redir_r(t_list *lexered_params, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data);
unsigned int	check_token_streak(t_token *next_token, t_list *lexered_params);
t_parser	    *new_elem(size_t *size, t_list *lexered_params, t_data *data);
unsigned int	get_len_between_pipes(t_list *lexered_params);

#endif
