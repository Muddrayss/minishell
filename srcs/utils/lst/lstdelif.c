/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdelif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:47:47 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 17:22:17 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstdelif(t_list **const lst, bool (*f)(const void *const), void (*del)(const void *const))
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	while (tmp)
	{
		if (f(tmp->content) == true)
		{
			next = tmp->next;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				*lst = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			lstdelone(tmp, del);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
}
