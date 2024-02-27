/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/02/27 19:04:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int8_t   check_syntax(t_list *lexered_params);
static int8_t   check_parenthesis(t_list *lexered_params);
static int8_t   check_redirs(t_list *lexered_params);
static t_tree   *fill_tree(t_list *lexered_params, t_list *stop);
static t_cmd    *init_cmd(char *cmd_str);
static t_list   *skip_parenthesis(t_list *lexered_params);
static t_list   *unskip_parenthesis(t_list *lexered_params);

t_tree	*parser(t_list *lexered_params)
{
    t_data *data;

    data = get_data();
    lstdelif(&lexered_params, &is_empty_cmd, &del_content_lexer);
    merge_separators(&lexered_params);
    if (check_syntax(lexered_params) == -1)
    {
        g_status = 2;
        return (NULL);
    }
    data->parsed_params = (t_tree **)malloc_p(sizeof(t_tree *));
    *(data->parsed_params) = fill_tree(lexered_params, NULL);
    return (*(data->parsed_params));
}

static int8_t   check_syntax(t_list *lexered_params)
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
        {
            if (!prev_elem || !next_elem || !prev_elem->cmd_str || !next_elem->cmd_str)
            {
                if (!prev_elem || !next_elem || prev_elem->token == SUBSHELL_START || next_elem->token == SUBSHELL_END)
                {  
                    ft_putstr_fd("minishell: syntax error near unexpected token: '", STDERR_FILENO);
                    write(STDERR_FILENO, &g_parser_tokens[(int)elem->token], 1);
                    write(STDERR_FILENO, "'\n", 2);
                    return (-1);
                }
            }
        }
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
                return (ft_putstr_fd("minishell: syntax error near unexpected token: ')'\n", STDERR_FILENO), -1);
        }
        lexered_params = lexered_params->next;
    }
    if (n_open)
        ft_putstr_fd("minishell: syntax error near unexpected token: '('\n", STDERR_FILENO);
    return (-1 * (n_open > 0)); //se ci sono parentesi aperte, ritorna -1
}

//deve comparare i caratteri ph_redir_r e ph_redir_l (NON i caratteri > e <)
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

//stop parte da NULL
static t_tree   *fill_tree(t_list *lexered_params, t_list *stop)
{
    t_tree  *node;
    t_lexer *elem;
    t_lexer *next_elem;

    if (!lexered_params) //forse inutile
        return (NULL);
    elem = (t_lexer *)lexered_params->content;
    if (elem->token == SUBSHELL_START)
        return (fill_tree(skip_parenthesis(lexered_params), stop));
    if (lexered_params->next == stop)
    {
        node = treenew_p(END, init_cmd(NULL)); //uso END come nodo vuoto, che serve solo per poter mettere il comando a sinistra invece che destra. così l'executor i comandi li ha solo a sinistra
        if (elem->token == SUBSHELL_END)
            treeadd_below(&node, fill_tree(unskip_parenthesis(lexered_params), lexered_params));
        else
            treeadd_below(&node, treenew_p(elem->token, init_cmd(elem->cmd_str)));
        return (node);
    }
    next_elem = (t_lexer *)lexered_params->next->content;
    node = treenew_p(next_elem->token, init_cmd(next_elem->cmd_str));
    if (elem->token != SUBSHELL_END)
        treeadd_below(&node, treenew_p(elem->token, init_cmd(elem->cmd_str)));
    else
        treeadd_below(&node, fill_tree(unskip_parenthesis(lexered_params), lexered_params));
    treeadd_below(&node, fill_tree(lexered_params->next->next, stop));
    return (node);
}

static t_list	*skip_parenthesis(t_list *lexered_params)
{
	int32_t	    n_open;
	t_lexer		*elem;

	n_open = 1;
	while (n_open && lexered_params->next)
	{
        lexered_params = lexered_params->next;
		elem = (t_lexer *)lexered_params->content;
		if (elem->token == SUBSHELL_END)
			n_open--;
		else if (elem->token == SUBSHELL_START)
			n_open++;
	}
	return (lexered_params); //ritorna la parentesi chiusa
}

static t_list   *unskip_parenthesis(t_list *lexered_params)
{
    int32_t    n_close;
    t_lexer    *elem;

    n_close = 1;
    while (n_close && lexered_params->prev)
    {
        lexered_params = lexered_params->prev;
        elem = (t_lexer *)lexered_params->content;
        if (elem->token == SUBSHELL_END)
            n_close++;
        else if (elem->token == SUBSHELL_START)
            n_close--;
    }
    return (lexered_params->next); //ritorna uno dopo la parentesi aperta
}

static t_cmd    *init_cmd(char *cmd_str)
{
    t_cmd   *cmd;

    //TODO gestire caso con solo heredoc senza testo
    cmd = malloc_p(sizeof(t_cmd));
    cmd->redirs = fill_redirs(cmd_str);
    cmd_str = clear_redirs(cmd->redirs, cmd_str);
    if (cmd_str)
    {
        cmd->cmd_str = ft_strdup(cmd_str);
        if (!cmd->cmd_str)
            ft_quit(ERR_MEM, "Error: failed to allocate memory");
    }
    else
        cmd->cmd_str = NULL;
    return (cmd);
}

void    restore_placeholders(char *cmd_str, char placeholder)
{
    uint32_t            i;

    i = -1;
    while (cmd_str[++i])
        if (cmd_str[i] == placeholder)
            cmd_str[i] = (placeholder * -1);
}


