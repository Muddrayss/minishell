/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdelone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:44:27 by egualand          #+#    #+#             */
/*   Updated: 2024/03/02 13:12:39 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst|| !del)
		return ;
	del(lst->content);
	ft_freenull((void **)&lst);
}