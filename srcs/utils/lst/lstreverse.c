/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstreverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:23:00 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 17:23:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstreverse(t_list **const lst)
{
	t_list	*prev;
	t_list	*next;

	prev = NULL;
	while (*lst)
	{
		next = (*lst)->next;
		(*lst)->next = prev;
		(*lst)->prev = next;
		prev = *lst;
		*lst = next;
	}
	*lst = prev;
}
