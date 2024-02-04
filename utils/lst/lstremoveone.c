/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstremoveone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:28:08 by egualand          #+#    #+#             */
/*   Updated: 2024/02/04 15:28:50 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	lstremoveone(t_list *to_remove, void (*del)(void *))
{
    t_list *tmp;

    tmp = to_remove->next;
    to_remove->next = tmp->next;
    tmp->next = NULL;
    lstdelone(to_remove, del);
}