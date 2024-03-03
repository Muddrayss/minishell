/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdelone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:44:27 by egualand          #+#    #+#             */
/*   Updated: 2024/03/03 16:49:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstdelone(const t_list *const lst, void (*del)(const void *const))
{
	if (!lst|| !del)
		return ;
	del(lst->content);
	free_and_null((void **)&lst);
}