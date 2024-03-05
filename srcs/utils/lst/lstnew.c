/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:24 by egualand          #+#    #+#             */
/*   Updated: 2024/03/06 00:05:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_list	*lstnew(const void *const content, const bool is_resource_stack)
{
	t_list	*new_node;

	if (is_resource_stack)
		new_node = (t_list *)malloc(sizeof(t_list));
	else
		new_node = (t_list *)malloc_p(sizeof(t_list)); //onn malloc_p altrimenti va in loop infinito
	if (!new_node)
		ft_quit(ERR_MEM, "minishell: failed to allocate memory");
	new_node->content = (void *)content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
