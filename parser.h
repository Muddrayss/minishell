/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:23 by craimond          #+#    #+#             */
/*   Updated: 2024/01/07 00:13:36 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
    char    **cmd_args; //include il primo (comando effettivo) + argomenti

    
}               t_parser;

/*

casi input:

- (<< limiter cmd)
- (infile < cmd)
- (cmd <&n)             prende come input al comando il fd numero n

casi extra:

- (n3< infile.txt)      apre infile.txt sul fd n per un utilizzo futuro
- (n<&-)                chiude il fd numero n

casi output:

- (cmd > outfile)
- (cmd >> outfile)
- (cmd >&n)             scrive l'output sul fd n    
- (cmd >>&n)            appende l'output sul fd n

n deve essere compreso tra 0 e 1023 incluso (fdmax), altrimenti e' interpretato come argomento e non fd
un numero n superiore al fdmax e' interpretato come argomento ANCHE SE NON CI SONO SPAZI prima del '>'

il parser si puo accorgere di questi casi specifici perche' la stringa dopo il '>' mantiene o meno gli spazi/tabs

*/
#endif