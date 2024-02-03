/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeadd_below.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:37:05 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 19:58:07 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    treeadd_below(t_tree **leaf, t_tree *new)
{
    if (!leaf)
        return ;
    if (*leaf == NULL)
        *leaf = new;
    else
    {
        if (!leaf->left)
            leaf->left = new;
        else
            leaf->right = new;
    }
}