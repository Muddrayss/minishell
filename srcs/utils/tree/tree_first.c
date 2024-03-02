/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_first.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:00:05 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 23:16:59 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_tree *tree_first(t_tree *root)
{
    if (!root)
        return (NULL);
    while (root->left)
        root = root->left;
    return (root);
}