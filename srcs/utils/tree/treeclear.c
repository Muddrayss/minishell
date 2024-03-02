/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeclear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:42:45 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 00:47:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	treeclear(t_tree **tree, void (*del)(void *))
{
    if (!tree || !*tree)
        return ;
    treeclear(&(*tree)->left, del);
    treeclear(&(*tree)->right, del);
    del((*tree)->content);
    (*tree)->content = NULL;
    ft_freenull((void **)tree);
}