/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:21:10 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 17:51:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstadd_front(t_list **const lst, t_list *const new)
{
    if (!lst || !new)
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
