/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treenew_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:37:35 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 19:53:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_tree	*treenew_p(int8_t type, char *cmd)
{
    t_tree	    *new_node;
    
    new_node = malloc_p(sizeof(t_tree));
    new_node->type = type;
    new_node->cmd = cmd;
    new_node->left = NULL;
    new_node->right = NULL;
    return (new_node);
}