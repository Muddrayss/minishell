/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeclear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:42:45 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 16:44:49 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	treeclear(t_tree **const tree, void (*del)(const void *const))
{
    if (!tree || !*tree)
        return ;
    treeclear(&(*tree)->left, del);
    treeclear(&(*tree)->right, del);
    del((*tree)->content);
    (*tree)->content = NULL;
    free_and_null((void **)tree);
}