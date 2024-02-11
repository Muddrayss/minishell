/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:21:10 by craimond          #+#    #+#             */
/*   Updated: 2024/02/12 00:05:46 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstadd_front(t_list **lst, t_list *new)
{
    if (!lst)
        return ;
    else if (!*lst)
        *lst = new;
    else
    {
        new->next = *lst;
        (*lst)->prev = new;
        *lst = new;
    }
}