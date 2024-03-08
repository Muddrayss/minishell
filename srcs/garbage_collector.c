/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:03 by craimond          #+#    #+#             */
/*   Updated: 2024/03/08 16:26:32 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static t_list	**gc_get(void);

void	gc_add(const void *const ptr)
{
	t_list	**gc;

	gc = gc_get();
	lstadd_front(gc, lstnew(ptr, PERM));
}

void	gc_cleanup(void)
{
	lstclear(gc_get(), free);
}

static t_list	**gc_get(void)
{
	static t_list	*gc;

	return (&gc);
}
