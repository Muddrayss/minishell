/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstremoveif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:47:47 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 14:13:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstremoveif(t_list **const lst, bool (*f)(const void *const), void (*del)(void *))
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
