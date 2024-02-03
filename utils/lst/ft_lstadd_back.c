/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:58 by egualand          #+#    #+#             */
/*   Updated: 2024/02/03 13:22:07 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
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