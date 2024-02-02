/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:26:33 by craimond          #+#    #+#             */
/*   Updated: 2024/01/29 21:26:36 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_if(t_list **lst, bool (*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*to_free;

	tmp = *lst;
	prev = NULL;
	to_free = NULL;
	while (tmp)
	{
		if (f(tmp->content) == true)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = tmp->next;
			to_free = tmp;
		}
		else
		{
			prev = tmp;
			to_free = NULL;
		}
		tmp = tmp->next;
		ft_lstdelone(to_free, del); // se to_free e' null, non fa nulla
	}
}