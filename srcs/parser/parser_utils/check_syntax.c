/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:03:13 by craimond          #+#    #+#             */
/*   Updated: 2024/03/04 16:52:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int8_t   check_tokens(const t_list *lexered_params);
static int8_t   check_parenthesis(const t_list *lexered_params);
static int8_t   check_redirs(const t_list *lexered_params);
static uint8_t  check_redir_streak(const char *const cmd_str);
static uint8_t  check_redir_pair(const char *const cmd_str);
static uint8_t  check_filename_presence(const char *const cmd_str);
static int8_t   check_quotes(const t_list *lexered_params);
static void     throw_syntax_error(const char token);

uint8_t   check_syntax(const t_list *const lexered_params)
{
    uint8_t  ret;

    ret = 0;
    ret += check_parenthesis(lexered_params);
    ret += check_tokens(lexered_params);
    ret += check_redirs(lexered_params);
    ret += check_quotes(lexered_params);
    return (ret > 0);
}

static int8_t    check_tokens(const t_list *lexered_params)
{
    t_lexer  *elem;
    t_lexer  *next_elem;
    t_lexer  *prev_elem;

    while (lexered_params)
    {
        elem = (t_lexer *)lexered_params->content;
        next_elem = NULL;
        prev_elem = NULL;
        if (lexered_params->next)
            next_elem = (t_lexer *)lexered_params->next->content;
        if (lexered_params->prev)
            prev_elem = (t_lexer *)lexered_params->prev->content;
        if (elem->token && elem->token != SUBSHELL_START && elem->token != SUBSHELL_END)
            if (!prev_elem || !next_elem || !prev_elem->cmd_str || !next_elem->cmd_str)
                if (!prev_elem || !next_elem || prev_elem->token == SUBSHELL_START || next_elem->token == SUBSHELL_END)
                    return (throw_syntax_error(g_parser_tokens[(int8_t)elem->token]), 1);
        lexered_params = lexered_params->next;
    }
    return (0);
}

static int8_t   check_parenthesis(const t_list *lexered_params)
{
    t_lexer     *elem;
    int16_t     n_open;

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
                return (throw_syntax_error(')'), 1);
        }
        lexered_params = lexered_params->next;
    }
    if (n_open)
        return (throw_syntax_error('('), 1);
    return (0); //se ci sono parentesi aperte, ritorna -1
}

static int8_t   check_redirs(const t_list *lexered_params)
{
    t_lexer     *elem;
    uint16_t    i;
    char        master_quote;
    uint8_t     ret;

    ret = 0;
    master_quote = '\0';
    while (lexered_params && ret == 0)
    {
        elem = (t_lexer *)lexered_params->content;
        i = 0;
        lexered_params = lexered_params->next;
        if (!elem->cmd_str)
            continue;
        while (elem->cmd_str[i])
        {
            if (is_quote(elem->cmd_str[i]))
            {
                if (master_quote == '\0')
                    master_quote = elem->cmd_str[i];
                else if (master_quote == elem->cmd_str[i])
                    master_quote = '\0';
            }
            else if (!master_quote && is_redir(elem->cmd_str[i]))
            {
                ret = check_redir_streak(elem->cmd_str + i);
                ret += check_redir_pair(elem->cmd_str + i);
                ret += check_filename_presence(elem->cmd_str + i);
            }
            i++;
        }
    }
    if (ret)
        return (throw_syntax_error(elem->cmd_str[i - 1]), 1);
    return (0);
}

static uint8_t check_redir_streak(const char *const cmd_str)
{
    uint16_t i;

    i = 0;
    while (cmd_str[i] && is_redir(cmd_str[i]))
        i++;
    return (i > 2);
}

static uint8_t check_redir_pair(const char *const cmd_str)
{
    return (is_redir(cmd_str[1]) && cmd_str[0] != cmd_str[1]);
}

static uint8_t check_filename_presence(const char *const cmd_str)
{
    return (is_empty_str(cmd_str + 1));
}

static int8_t check_quotes(const t_list *lexered_params)
{
    char        master_quote;
    uint16_t    i;
    t_lexer     *elem;

    i = 0;
    master_quote = '\0';
    while (lexered_params && master_quote == '\0')
    {
        elem = (t_lexer *)lexered_params->content;
        lexered_params = lexered_params->next;
        if (!elem->cmd_str)
            continue;
        while (elem->cmd_str[i])
        {
            if (!master_quote && is_quote(elem->cmd_str[i]))
                master_quote = elem->cmd_str[i];
            else if (elem->cmd_str[i] == master_quote)
                master_quote = '\0';
        }
    }
    if (master_quote)
        return (throw_syntax_error(master_quote), -1);
    return (0);
}

static void	throw_syntax_error(const char token)
{
    ft_putstr_fd("Syntax error near unexpected token: '", STDERR_FILENO);
    write(STDERR_FILENO, &token, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
