/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/01/08 15:00:48 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list    **parser(t_list **lexered_params_head)
{
    t_list	    **parsed_params_head;
    t_list      *lex_node;
    t_parser    *pars_content;
    t_lexer     *lex_content;
    char        *cmd_str;

    parsed_params_head = (t_list **)malloc(sizeof(t_list *));
    if (!parsed_params_head)
        ft_quit(12, "failed to allocate memory");
    pars_content = init_elem();
    lex_node = *lexered_params_head;
    while (lex_node)
    {
        lex_content = (t_lexer *)lex_node->content;
        if (lex_content->type == CMD)
            ft_strjoin(cmd_str, lex_content->str.cmd);
        if (lex_content->type == TOKEN)
        {
            if (lex_content->str.token == PIPE)
            {
                ft_lstadd_back(parsed_params_head, ft_lstnew(pars_content));
                pars_content = new_elem();
            }
        }
        lex_node = lex_node->next;
    }
    return (parsed_params_head);
}

static t_parser *new_elem(void)
{
    t_parser    *elem;

    elem = (t_parser *)malloc(sizeof(t_parser));
    if (!elem)
        ft_quit(10, "failed to allocate memory");
    elem->cmd_args = NULL;
    elem->vars = (t_list **)malloc(sizeof(t_list *));
    if (!elem->vars)
        ft_quit(11, "failed to allocate memory");
    elem->vars = NULL;
}