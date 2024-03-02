/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeadd_below.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:37:05 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 23:03:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_tree  *treeadd_below(t_tree *node, t_tree *new)
{
    if (!node)
        return (new);
    else
    {
        if (!node->left)
            node->left = new;
        else
            node->right = new;
    }
    return (node);
}