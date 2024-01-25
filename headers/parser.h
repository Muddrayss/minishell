/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/01/25 19:24:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define LEFT 0
# define RIGHT 1

# define PH_REDIR -42
# define PH_INVALID_ENV -43
# define PH_ABS_PATH -44

# define CMD_LEN 0
# define ENV_NUM 1

// TODO sostituire ogni enum con variabili di un singolo byte

typedef enum e_redir_type
{
	REDIR_INPUT,	 // '< filename'
	REDIR_HEREDOC,	 // '<< limiter'
	REDIR_INPUT_FD,	 // '<&n'
	REDIR_OUTPUT,	 // '> filename o n> filename'
	REDIR_OUTPUT_FD, // '>&n'
	REDIR_APPEND,	 // '>> filename o n>> filename'
	REDIR_APPEND_FD, // '>>&n'
}
t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	int				fds[2];
	char 			*filename; // o limiter in caso dell heredoc
}					t_redir;

typedef struct s_parser
{
	char	*cmd_str;
	char	*bin_path; //null se il comando e' un builtin, altrimenti path del binario (con PH_CWD se c'e' il ./)
	t_list	*redirs;
	pid_t 	pid;
} t_parser;

t_list			*parser(t_list *lexered_params, t_data *data);
void			handle_redir_l(t_list *lexered_params, t_parser *content_par, t_data *data);
void			handle_redir_r(t_list *lexered_params, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data);
unsigned int	check_token_streak(t_token *next_token, t_list *lexered_params);
t_parser		*new_elem(size_t *size, t_list *lexered_params, t_data *data);
void			remove_filename(char **str, unsigned int *starting_idx, t_data *data);
void			remove_num(char **str, unsigned int *starting_idx, uint8_t flag, t_data *data);
void 			replace_env_var(char **str, char *env_var, t_data *data);
t_lexer 		*get_next_cmd_elem(t_list *lexered_params);
bool			is_empty_cmd(void *content);
void			del_content_redirs(void *content);
void			del_content_parser(void *content);

#endif
