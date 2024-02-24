/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:24:52 by craimond          #+#    #+#             */
/*   Updated: 2024/02/24 14:58:48 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
        node = node->next;
    }
    printf("stringa finale: %s\n", ((t_lexer *)(*lexered_params)->content)->cmd_str);
}

static void merge_ampersands(t_list **head, t_list **node)
{
    t_lexer *elem;
    t_lexer *next_elem;
    t_lexer *prev_elem;
    t_list  *node_prev;
    char    *tmp;

    next_elem = NULL;
    prev_elem = NULL;
    //TODO gestire i segfault di next e prev
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
        free(tmp);
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

bool    is_empty_cmd(void *content)
{
    t_lexer *elem;

    elem = (t_lexer *)content;
    if (elem->token == 0 && is_empty_str(elem->cmd_str))
        return (true);
    return (false);
}

void    del_content_parser(void *content)
{
    t_tree  *elem;

    elem = (t_tree *)content;
    lstclear(&elem->cmd->redirs, &del_content_redirs);
    free(elem->cmd->cmd_str);
    free(elem->cmd);
}

void    del_content_redirs(void *content)
{
    t_redir *elem;

    elem = (t_redir *)content;
    free(elem->filename);
    free(content);
}
