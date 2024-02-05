/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeclear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:42:45 by craimond          #+#    #+#             */
/*   Updated: 2024/02/05 16:16:30 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: implement treeclear

#include "../../headers/minishell.h"

void	treeclear(t_tree **tree, void (*del)(void *))
{
    if (*tree == NULL)
        return ;
    treeclear(&(*tree)->left, del);
    treeclear(&(*tree)->right, del);
    del(*tree);
    free(*tree);
    *tree = NULL;
}