/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:21:10 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 23:29:32 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstadd_front(t_list **lst, t_list *new)
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
