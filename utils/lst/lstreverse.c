/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstreverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:38:02 by craimond          #+#    #+#             */
/*   Updated: 2024/02/07 15:45:58 by craimond         ###   ########.fr       */
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
        prev = *lst;
        *lst = next;
    }
    *lst = prev;
}