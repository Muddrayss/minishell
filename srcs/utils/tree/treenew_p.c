/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treenew_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:37:35 by craimond          #+#    #+#             */
/*   Updated: 2024/02/06 15:32:56 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_tree	*treenew_p(int8_t type, t_cmd *cmd)
{
    t_tree	    *new_node;
    
    new_node = malloc_p(sizeof(t_tree));
    new_node->type = type;
    new_node->cmd = cmd;
    new_node->left = NULL;
    new_node->right = NULL;
    return (new_node);
}