/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:02:15 by codespace         #+#    #+#             */
/*   Updated: 2024/03/06 19:10:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	lstclear(t_list **lst, void (*del)(void *))
{
    t_list	*tmp;

    if (!lst || !*lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        if (del)
            del((*lst)->content);
        (*lst)->content = NULL;
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}