/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:09:09 by craimond          #+#    #+#             */
/*   Updated: 2024/02/02 16:49:35 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*ft_treenew(int8_t type, char *cmd)
{
    t_tree	    *new_node;
    
    new_node = malloc(sizeof(t_tree));
    if (!new_node)
        return (NULL);
    new_node->type = type;
    new_node->cmd = cmd;
    new_node->branches = NULL;
    return (new_node);
}

void    ft_treeadd_below(t_tree **head, t_tree *new)
{
    t_tree	*last;
    
    if (!head)
        return ;
    if (*head == NULL)
        *head = new;
    else
    {
        last = ft_tree_last(*head); //traversa e trova il piu' a destra
        (*head)->n_branches++;
        ft_lstadd_back(last->branches->branches_list, new);
    }
}

t_tree	*ft_tree_last(t_tree *head)
{
    t_tree    *last;

    if (!head)
        return (NULL);
    last = ft_lstlast(head->branches->branches_list);
    return (last);
}

ft_tree_size(t_tree *node, int size)
{
    t_list    *branches_list;

    if (!node)
        return (size);
    if (node)
        size++;
    branches_list = node->branches.branches_list;
    ft_tree_size(branches_list->prev, size);
    ft_tree_size(branches_list->next, size);
}
