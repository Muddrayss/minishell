/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:21:24 by egualand          #+#    #+#             */
/*   Updated: 2024/02/04 15:29:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_list	*lstnew_p(void *content)
{
	t_list	*new_node;

	new_node = malloc_p(sizeof(t_list));
	new_node->content = content;
	new_node->next = NULL;
    new_node->prev = NULL;
	return (new_node);
}