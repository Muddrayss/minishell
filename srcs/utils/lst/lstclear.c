/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:45:40 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 23:34:52 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstclear(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}