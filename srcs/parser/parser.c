/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 14:36:42 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_tree   *fill_tree(t_list *lexered_params, t_list *stop);
static t_parser *init_cmd(char type, char *cmd_str);
static t_list   *skip_parenthesis(t_list *lexered_params);
static t_list   *unskip_parenthesis(t_list *lexered_params);

void    parser(t_list *lexered_params)
{
    lstdelif(&lexered_params, &is_empty_cmd, &del_content_lexer);
    merge_separators(&lexered_params);
    if (check_syntax(lexered_params) == -1)
    {
        g_status = 2;
        return ;
    }
    get_data()->parsed_params = fill_tree(lexered_params, NULL);
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
        node = treenew_p(init_cmd(END, NULL)); //uso END come nodo vuoto, che serve solo per poter mettere il comando a sinistra invece che destra. così l'executor i comandi li ha solo a sinistra
        if (elem->token == SUBSHELL_END)
            node = treeadd_below(node, fill_tree(unskip_parenthesis(lexered_params), lexered_params));
        else
            node = treeadd_below(node, treenew_p(init_cmd(elem->token, elem->cmd_str)));
        return (node);
    }
    next_elem = (t_lexer *)lexered_params->next->content;
    node = treenew_p(init_cmd(next_elem->token, next_elem->cmd_str));
    if (elem->token != SUBSHELL_END)
        node = treeadd_below(node, treenew_p(init_cmd(elem->token, elem->cmd_str)));
    else
        node = treeadd_below(node, fill_tree(unskip_parenthesis(lexered_params), lexered_params));
    node = treeadd_below(node, fill_tree(lexered_params->next->next, stop));
    return (node);
}

static t_list	*skip_parenthesis(t_list *lexered_params)
{
	t_lexer		*elem;
	uint16_t	n_open;

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
    t_lexer    *elem;
    uint16_t   n_close;

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

static t_parser *init_cmd(char type, char *cmd_str)
{
    t_parser    *node;
    t_cmd       *cmd;
    

    node = (t_parser *)malloc_p(sizeof(t_parser));
    cmd = (t_cmd *)malloc_p(sizeof(t_cmd));
    node->cmd = cmd;
    node->type = type;
    cmd->cmd_str = NULL;
    cmd->redirs = NULL;
    if (cmd_str)
    {
        cmd->redirs = fill_redirs(cmd_str);
        cmd->cmd_str = clear_redirs(cmd_str);
    }
    return (node);
}


