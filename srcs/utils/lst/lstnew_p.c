/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:24 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 17:22:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_list	*lstnew_p(const void *const content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc_p(sizeof(t_list));
	new_node->content = (void *)content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
