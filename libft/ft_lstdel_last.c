/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:24:56 by egualand          #+#    #+#             */
/*   Updated: 2024/01/30 15:25:51 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_last(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*prev;

	if (!lst || !del || !*lst)
		return ;
	tmp = *lst;
	prev = NULL;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
		prev->next = NULL;
	ft_lstdelone(tmp, del);
}
