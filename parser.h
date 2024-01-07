/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/01/07 18:14:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_vars
{
	char			*name;
	char			*value; //con getenv(name);
	struct s_vars	*next;
}	t_vars;

typedef struct s_parser //tra | e |
{
    char	**cmd_args;
	//aggiungere un qualcosa per le redirections (infinite '>' '<' '>>' '<<')
	t_list	**vars;	//lista di variabili d'ambiente create con $
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