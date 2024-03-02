/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:07:33 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 16:00:21 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	del_content_lexer(void *content)
{
	t_lexer	*elem;

	elem = (t_lexer *)content;
	free_and_null((void **)&elem->cmd_str);
    free_and_null((void **)&elem);
}