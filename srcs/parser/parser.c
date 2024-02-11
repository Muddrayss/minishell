/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/02/12 00:10:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int8_t   check_syntax(t_list *lexered_params);
static t_tree   *fill_tree(t_list *lexered_params, t_list *stop);
static t_cmd    *init_cmd(char *cmd_str);
static t_list   *skip_parenthesis(t_list *lexered_params);
static t_list   *unskip_parenthesis(t_list *lexered_params);

t_tree	*parser(t_list *lexered_params)
{
    t_tree   **parsed_params;

    lstdelif(&lexered_params, &is_empty_cmd, &del_content_lexer);
    check_syntax(lexered_params);
    merge_separators(&lexered_params);
    parsed_params = (t_tree **)malloc_p(sizeof(t_tree *));
    *parsed_params = fill_tree(lexered_params, NULL);
    return (*parsed_params);
}

static int8_t   check_syntax(t_list *lexered_params)
{
    //TODO 
    (void)lexered_params;
    return (0);
}

//stop parte da NULL
static t_tree *fill_tree(t_list *lexered_params, t_list *stop)
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
        node = treenew_p(END, NULL); //uso END come nodo vuoto, che serve solo per poter mettere il comando a sinistra invece che destra. così l'executor i comandi li ha solo a sinistra
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

//TODO da mergiare con unskip_parenthesis (int8_t direction)
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

    if (!cmd_str)
        return (NULL);
    cmd = malloc_p(sizeof(t_cmd));
    cmd->redirs = fill_redirs(cmd_str);
    clear_redirs(cmd->redirs, cmd_str);
    cmd->cmd_str = cmd_str;
    return (cmd);
}


