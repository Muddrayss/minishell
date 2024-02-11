/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:36:45 by craimond          #+#    #+#             */
/*   Updated: 2024/02/12 00:08:29 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

uint32_t tree_size(t_tree *node, uint32_t size)
{
    if (!node)
        return (size);
    if (node)
        size++;
    size += tree_size(node->left, size);
    size += tree_size(node->right, size);
    return (size);
}