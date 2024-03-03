/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeadd_below.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:37:05 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 16:51:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_tree  *treeadd_below(t_tree *const node, const t_tree *const new)
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