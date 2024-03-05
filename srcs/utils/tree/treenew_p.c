/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treenew_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:37:35 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 17:28:57 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_tree	*treenew_p(const void *const content)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc_p(sizeof(t_tree));
	new_node->content = (void *)content;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
