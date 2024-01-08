/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/01/08 19:08:27 by craimond         ###   ########.fr       */
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
    int                 fd;         // se serve, altrimenti -42
    char				*filename; 	// se serve (nome file o limiter dell'here_doc), altrimenti NULL
}	t_redirection;

//TODO aggiungere un placeholder in cmd_args per ricordarsi a che punto eseguire una redirection

typedef struct s_parser
{
    char	**cmd_args;
	t_list	**redirections;
	t_list	**vars;
}	t_parser;

/*

casi input:

- (<< limiter cmd)
- (infile < cmd)
- (cmd <&n)             prende come input al comando il fd numero n

casi extra:

- (n< infile)           apre infile sul fd n per un utilizzo futuro
- (n<&-)                chiude il fd numero n
- (n> outfile)			redirige l'output che andrebbe sull FD 3 nell outfile
- (<> outfile)          apre outfile sia per read che per write

casi output:

- (cmd > outfile)
- (cmd >> outfile)
- (cmd >&n)             scrive l'output sul fd n    
- (cmd >>&n)            appende l'output sul fd n

casi strani:

- (> outfile)           crea o ricrea (sovrascrivendo) il file outfile

- (> outfile)           crea un here_doc fino al ctrl+D e mette il contenuto dentro out (COMPORTAMENTO NON STANDARD)
- (> outfile cmd)       scrive l'output del comando sull'outfile (COMPORTAMENTO NON STANDARD)

il parser si puo accorgere di questi casi specifici perche' la stringa dopo il '>' mantiene o meno gli spazi/tabs

*/
#endif