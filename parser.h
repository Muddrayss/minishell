/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/01/07 18:48:31 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_redirection_type
{
    REDIR_INPUT,        // '<'
    REDIR_OUTPUT,       // '>'
    REDIR_APPEND,       // '>>'
    REDIR_HEREDOC,      // '<<'
    REDIR_INPUT_FD,     // '<&n'
    REDIR_OUTPUT_FD,    // '>&n'
    REDIR_APPEND_FD,    // '>>&n'
    REDIR_INPUT_DUP,    // 'n<'
    REDIR_OUTPUT_DUP,   // 'n>'
    REDIR_CLOSE_FD      // 'n<&-'
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
    int                 fd;         // FD per casi come (n<, >&n, n<&- etc.), altrimenti -42
    char				*filename; 	// nome del file o LIMITER dell'heredoc
}	t_redirection;

//TODO aggiungere un placeholder per ricordarsi a che punto eseguire una redirection

typedef struct s_parser //tra | e |
{
    char	**cmd_args;
	t_list	**redirections;	//lista di redirections
	t_list	**vars;			//lista di variabili d'ambiente create con $
}	t_parser;

/*

casi input:

- (<< limiter cmd)
- (infile < cmd)
- (cmd <&n)             prende come input al comando il fd numero n

casi extra:

- (n< infile)          apre infile sul fd n per un utilizzo futuro
- (n<&-)                chiude il fd numero n
- (n> outfile)			redirige l'output che andrebbe sull FD 3 nell outfile

casi output:

- (cmd > outfile)
- (cmd >> outfile)
- (cmd >&n)             scrive l'output sul fd n    
- (cmd >>&n)            appende l'output sul fd n

casi strani:

- (> outfile)           crea o ricrea (sovrascrivendo) il file outfile

- (> outfile)           crea un here_doc fino al ctrl+D e mette il contenuto dentro out (COMPORTAMENTO NON STANDARD)
- (> outfile cmd)       scrive l'output del comando sull'outfile (COMPORTAMENTO NON STANDARD)

n deve essere compreso tra 0 e 1023 incluso (fdmax), altrimenti e' interpretato come argomento e non fd
un numero n superiore al fdmax e' interpretato come argomento ANCHE SE NON CI SONO SPAZI prima del '>'

il parser si puo accorgere di questi casi specifici perche' la stringa dopo il '>' mantiene o meno gli spazi/tabs

*/
#endif