/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:24 by egualand          #+#    #+#             */
/*   Updated: 2024/03/06 15:15:48 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_list	*lstnew(const void *const content, const uint8_t alloc_type)
{
	t_list	*new_node;

	new_node = (t_list *)malloc_p(sizeof(t_list), alloc_type);
	new_node->content = (void *)content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
