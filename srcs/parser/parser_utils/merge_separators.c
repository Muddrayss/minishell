/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:59:34 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 15:32:50 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void merge_ampersands(t_list **head, t_list **node);
static void merge_pipes(t_list **head, t_list **node);

void merge_separators(t_list **lexered_params)
{
    t_list  *node;
    t_lexer *elem;

    node = *lexered_params;
    while (node)
    {
        elem = (t_lexer *)node->content;
        if (elem->token)
        {
            if (elem->token == '&')
                merge_ampersands(lexered_params, &node);
            else if (elem->token == '|')
                merge_pipes(lexered_params, &node);
            else if (elem->token == '(')
                elem->token = SUBSHELL_START;
            else if (elem->token == ')')
                elem->token = SUBSHELL_END;
            else if (elem->token == ';')
                elem->token = SEMICOLON;
        }
        if (node)
            node = node->next;
    }
}

//TODO refractor
static void merge_ampersands(t_list **head, t_list **node)
{
    t_lexer *elem;
    t_lexer *next_elem;
    t_lexer *prev_elem;
    t_list  *node_prev;
    char    *tmp;

    next_elem = NULL;
    prev_elem = NULL;
    elem = (t_lexer *)(*node)->content;
    if ((*node)->next)
        next_elem = (t_lexer *)(*node)->next->content;
    if ((*node)->prev)
        prev_elem = (t_lexer *)(*node)->prev->content;
    if (next_elem && next_elem->token == '&')
    {
        elem->token = AND;
        lstremoveone(head, (*node)->next, &del_content_lexer);
    }
    else if (prev_elem && next_elem && prev_elem->cmd_str)
    {
        tmp = prev_elem->cmd_str;
        prev_elem->cmd_str = (char *)malloc_p(sizeof(char) * (ft_strlen(prev_elem->cmd_str) + ft_strlen(next_elem->cmd_str) + 2));
        ft_strcpy(prev_elem->cmd_str, tmp);
        ft_strcat(prev_elem->cmd_str, "&");
        ft_strcat(prev_elem->cmd_str, next_elem->cmd_str);
        free_and_null((void **)&tmp);
        node_prev = (*node)->prev;
        lstremoveone(head, (*node)->next, &del_content_lexer);
        lstremoveone(head, (*node), &del_content_lexer);
        *node = node_prev;
    }
}

static void merge_pipes(t_list **head, t_list **node)
{
    t_lexer *elem;
    t_lexer *next_elem;
    t_list  *node_prev;

    next_elem = NULL;
    elem = (t_lexer *)(*node)->content;
    if ((*node)->next)
        next_elem = (t_lexer *)(*node)->next->content;
    if (next_elem && next_elem->token == '|')
    {
        elem->token = OR;
        node_prev = (*node)->prev;
        lstremoveone(head, (*node)->next, del_content_lexer);
        *node = node_prev;
    }
    else
        elem->token = PIPELINE;
}