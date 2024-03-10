/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstremoveif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:47:47 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:12:56 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstremoveif(t_list **const lst,
	bool (*f)(const void *const), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	while (tmp)
	{
		if (f(tmp->content) == true)
		{
			next = tmp->next;
			lstremoveone(lst, tmp, del);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
}
