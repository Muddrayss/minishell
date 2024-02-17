/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:19:28 by craimond          #+#    #+#             */
/*   Updated: 2024/02/17 14:44:08 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void lstsort(t_list *lst, int (*swap_condition)(char *, char *))
{
    t_list  *tmp;
    void    *content;

    while (lst)
    {
        tmp = lst->next;
        while (tmp)
        {
            if (swap_condition(lst->content, tmp->content) > 0)
            {
                content = lst->content;
                lst->content = tmp->content;
                tmp->content = content;
            }
            tmp = tmp->next;
        }
        lst = lst->next;
    }
}
