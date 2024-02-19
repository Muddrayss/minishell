/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:46:17 by craimond          #+#    #+#             */
/*   Updated: 2024/02/19 15:53:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void    lstsort(t_list *lst, int (*swap_condition)())
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