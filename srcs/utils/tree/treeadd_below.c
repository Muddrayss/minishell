/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeadd_below.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:10:55 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 16:10:57 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_tree	*tb(t_tree *const node, const t_tree *const new)
{
	if (!node)
		return ((t_tree *)new);
	else
	{
		if (!node->left)
			node->left = (t_tree *)new;
		else
			node->right = (t_tree *)new;
	}
	return (node);
}
