/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeadd_below.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:37:05 by craimond          #+#    #+#             */
/*   Updated: 2024/02/12 00:08:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void    treeadd_below(t_tree **node, t_tree *new)
{
    if (!node)
        return ;
    if (*node == NULL)
        *node = new;
    else
    {
        if (!(*node)->left)
            (*node)->left = new;
        else
            (*node)->right = new;
    }
}