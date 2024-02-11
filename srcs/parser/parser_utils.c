/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:24:52 by craimond          #+#    #+#             */
/*   Updated: 2024/02/11 23:30:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void merge_ampersands(t_list **head, t_list *node);
static void merge_pipes(t_list **head, t_list *node);

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
                merge_ampersands(lexered_params, node);
            else if (elem->token == '|')
                merge_pipes(lexered_params, node);
            else if (elem->token == '(')
                elem->token = SUBSHELL_START;
            else if (elem->token == ')')
                elem->token = SUBSHELL_END;
            else if (elem->token == ';')
                elem->token = SEMICOLON;
        }
        node = node->next;
    }
}

static void merge_ampersands(t_list **head, t_list *node)
{
    t_lexer *elem;
    t_lexer *next_elem;
    t_lexer *prev_elem;

    //vanno in segfault se non ci sono due elementi prima e dopo (quindi e' da fare attentamente il check_syntax())
    elem = (t_lexer *)node->content;
    next_elem = (t_lexer *)node->next->content;
    prev_elem = (t_lexer *)node->prev->content;
    if (next_elem->token == '&')
        elem->token = AND;
    else
        ft_strcat(prev_elem->cmd_str, "&");
    lstremoveone(head, node->next, &del_content_lexer);
}

static void merge_pipes(t_list **head, t_list *node)
{
    t_lexer *elem;
    t_lexer *next_elem;

    elem = (t_lexer *)node->content;
    next_elem = (t_lexer *)node->next->content;
    if (next_elem->token == '|')
    {
        elem->token = OR;
        lstremoveone(head, node->next, del_content_lexer);
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
}
