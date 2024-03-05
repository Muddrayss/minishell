/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:36:37 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 17:21:52 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstadd_back(t_list **const lst, t_list *const new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	else if (!*lst)
		*lst = new;
	else
	{
		last = lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}
