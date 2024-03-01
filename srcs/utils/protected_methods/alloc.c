/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:40:05 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 18:19:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void    *malloc_p(size_t size)
{
    void    *ptr;

    if (size == 0)
        return (NULL);
    ptr = malloc(size);
    if (!ptr)
        ft_quit(ERR_MEM, "minishell: failed to allocate memory");
    return (ptr);
}

void    *calloc_p(size_t nmemb, size_t size)
{
    void    *ptr;

    if (nmemb == 0 || size == 0)
        return (NULL);
    ptr = ft_calloc(nmemb, size);
    if (!ptr)
        ft_quit(ERR_MEM, "minishell: failed to allocate memory");
    return (ptr);
}