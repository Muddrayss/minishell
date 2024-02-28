/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:03:13 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 00:22:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int8_t   check_parenthesis(t_list *lexered_params);
static int8_t   check_redirs(t_list *lexered_params);
static void     throw_syntax_error(char token);

int8_t   check_syntax(t_list *lexered_params)
{
    t_lexer  *elem;
    t_lexer  *next_elem;
    t_lexer  *prev_elem;

    if (check_parenthesis(lexered_params) == -1 || check_redirs(lexered_params) == -1)
        return (-1);
    while (lexered_params)
    {
        elem = (t_lexer *)lexered_params->content;
        next_elem = NULL;
        prev_elem = NULL;
        if (lexered_params->next)
            next_elem = (t_lexer *)lexered_params->next->content;
        if (lexered_params->prev)
            prev_elem = (t_lexer *)lexered_params->prev->content;
        if (elem->token && elem->token != SUBSHELL_START && elem->token != SUBSHELL_END) //escludere anche tutte le reidirs
            if (!prev_elem || !next_elem || !prev_elem->cmd_str || !next_elem->cmd_str)
                if (!prev_elem || !next_elem || prev_elem->token == SUBSHELL_START || next_elem->token == SUBSHELL_END)
                    return (throw_syntax_error(g_parser_tokens[(int)elem->token]), -1);
        lexered_params = lexered_params->next;
    }
    return (0);
}

static int8_t check_parenthesis(t_list *lexered_params)
{
    int32_t     n_open;
    t_lexer     *elem;

    n_open = 0;
    while (lexered_params)
    {
        elem = (t_lexer *)lexered_params->content;
        if (elem->token == SUBSHELL_START)
            n_open++;
        else if (elem->token == SUBSHELL_END)
        {
            n_open--;
            if (n_open < 0)
                return (throw_syntax_error(')'), -1);
        }
        lexered_params = lexered_params->next;
    }
    if (n_open)
        throw_syntax_error('(');
    return (-1 * (n_open > 0)); //se ci sono parentesi aperte, ritorna -1
}

static int8_t   check_redirs(t_list *lexered_params)
{
    //TODO
    /*
    REDIR_INPUT 		7 	'< filename cmd' o 'cmd < filename'
    REDIR_HEREDOC 		8	'<< limiter cmd' o 'cmd << limiter'
    REDIR_OUTPUT 		9 	'cmd > filename' o 'cmd n> filename'
    REDIR_APPEND 		10  'cmd >> filename' o 'cmd n>> filename'
    */
    (void)lexered_params;
    return (0);
}

static void	throw_syntax_error(char token)
{
	ft_putstr_fd("Syntax error near unexpected token'", STDERR_FILENO);
	write(STDERR_FILENO, &token, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}