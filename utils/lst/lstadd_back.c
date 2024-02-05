/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:58 by egualand          #+#    #+#             */
/*   Updated: 2024/02/05 11:54:52 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

    if (!lst)
        return ;
	else if (*lst == NULL)
		*lst = new;
	else
    {
        last = lstlast(*lst);
        last->next = new;
        new->prev = last;
    }
}