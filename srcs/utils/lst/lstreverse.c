/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstreverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:38:02 by craimond          #+#    #+#             */
/*   Updated: 2024/02/08 15:29:53 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    lstreverse(t_list **lst)
{
    t_list	*prev;
    t_list	*next;

    prev = NULL;
    while (*lst)
    {
        next = (*lst)->next;
        (*lst)->next = prev;
        (*lst)->prev = next;
        prev = *lst;
        *lst = next;
    }
    *lst = prev;
}

// 1 -> 2 -> 3 -> 4 -> 5 -> NULL
// prev = NULL
// next = 2
// 1 -> NULL
// prev = 1
// next = 3
// 2 -> 1 -> NULL
// prev = 2
// next = 4
// 3 -> 2 -> 1 -> NULL
// prev = 3
// next = 5
// 4 -> 3 -> 2 -> 1 -> NULL
// prev = 4
// next = NULL
// 5 -> 4 -> 3 -> 2 -> 1 -> NULL
// prev = 5
// next = NULL
// 5 -> 4 -> 3 -> 2 -> 1 -> NULL