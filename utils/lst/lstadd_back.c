/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:58 by egualand          #+#    #+#             */
/*   Updated: 2024/02/03 19:53:07 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

    if (!lst)
        return ;
	if (*lst == NULL)
		*lst = new;
	else
    {
        last = ft_lstlast(*lst);
        last->next = new;
        new->prev = last;
    }
}