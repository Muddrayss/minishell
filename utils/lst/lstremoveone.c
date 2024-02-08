/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstremoveone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:28:08 by egualand          #+#    #+#             */
/*   Updated: 2024/02/08 15:12:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    lstremoveone(t_list **head, t_list *to_remove, void (*del)(void *))
{
    t_list *prev;
    t_list *next;

    if (!to_remove)
        return ;
    prev = to_remove->prev;
    next = to_remove->next;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
    to_remove->next = NULL;
    to_remove->prev = NULL;
    if (to_remove == *head)
        *head = next;
    lstdelone(to_remove, del);
}