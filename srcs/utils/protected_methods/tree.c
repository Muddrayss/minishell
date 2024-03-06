/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:01:57 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 11:43:29 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_tree    *treenew_p(const void *const content)
{
	t_tree    *new_node;

	new_node = treenew(content);
	if (!new_node)
		ft_quit(ERR_MEM, "minishell: failed to allocate memory");
	lstadd_front(get_tmp_resources_stack(), lstnew(new_node, true));
	return (new_node);
}