/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:05:21 by craimond          #+#    #+#             */
/*   Updated: 2024/01/29 22:06:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list  *ft_lstdup_until(t_list *lst, void *stop)
{
    t_list                  *new_lst;
    static t_list           *node;
    static bool             over = false;
    t_list                  *new_node;

    if (over == true)
        return (NULL);
    if (!node)
        node = lst;
    new_lst = NULL;
    while (node && *((uintptr_t *)node->content) != *((uintptr_t *)stop))
    {
        new_node = ft_lstnew(node->content);
        if (!new_node)
            return(ft_lstclear(&new_lst, &free), NULL);
        ft_lstadd_back(&new_lst, new_node);
        node = node->next;
    }
    if (node)
        node = node->next;
    if (!node)
        over = true;
    return (new_lst);
}