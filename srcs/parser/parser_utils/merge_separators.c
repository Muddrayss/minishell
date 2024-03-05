/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:59:34 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 13:21:57 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void merge_pipes(t_list **const head, t_list **const node);
static void merge_ampersands(t_list **const head, t_list **const node);
static void combine_cmd_strings(t_list **const head, t_list **const node, t_lexer *const prev_elem, const t_lexer *const next_elem);

void merge_separators(t_list **const lexered_params)
{
    t_list  *node;
    t_lexer *elem;

    node = (t_list *)*lexered_params;
    while (node)
    {
        elem = (t_lexer *)node->content;
        if (elem->token)
        {
            if (elem->token == '|')
                merge_pipes(lexered_params, &node);
            else if (elem->token == '&')
                merge_ampersands(lexered_params, &node);
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

//TODO guardare caso in cui il comando e' '& wc' e basta
static void merge_ampersands(t_list **const head, t_list **const node)
{
    t_lexer *elem;
    t_lexer *next_elem;
    t_lexer *prev_elem;

    elem = (t_lexer *)(*node)->content;
    next_elem = NULL;
    if ((*node)->next)
    {
        next_elem = (t_lexer *)(*node)->next->content;
        if (next_elem->token == '&')
        {
            elem->token = AND;
            lstremoveone(head, (*node)->next, &del_content_lexer);
            return ;
        }
    }
    if ((*node)->prev)
    {
        prev_elem = (t_lexer *)(*node)->prev->content;
        if (prev_elem->cmd_str)
            combine_cmd_strings(head, node, prev_elem, next_elem);
    }
}

static void combine_cmd_strings(t_list **const head, t_list **const node, t_lexer *const prev_elem, const t_lexer *const next_elem)
{
    t_list      *node_prev;
    char        *tmp;
    uint16_t    size;

    size = ft_strlen(prev_elem->cmd_str) + 2;
    if (next_elem)
        size += ft_strlen(next_elem->cmd_str);
    tmp = prev_elem->cmd_str;
    prev_elem->cmd_str = (char *)malloc_p(sizeof(char) * size);
    ft_strcpy(prev_elem->cmd_str, tmp);
    ft_strcat(prev_elem->cmd_str, "&");
    if (next_elem)
    {
        ft_strcat(prev_elem->cmd_str, next_elem->cmd_str);
        lstremoveone(head, (*node)->next, &del_content_lexer);
    }
    free_and_null((void **)&tmp);
    node_prev = (*node)->prev;
    lstremoveone(head, (*node), &del_content_lexer);
    *node = node_prev;
}

static void merge_pipes(t_list **const head, t_list **const node)
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