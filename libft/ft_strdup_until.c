/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:16:31 by craimond          #+#    #+#             */
/*   Updated: 2024/01/31 21:54:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char    *ft_strdup_until(char *str, char *set, char *stopped_at)
{
    char                    *new_str;
    static char             *old_str = NULL;
    size_t                  size;
    static unsigned int     i = 0;
    char                    *tmp;

    tmp = NULL;
    if (old_str != str)
        i = 0;
    size = 0;
    while (str[i + size])
    {
        tmp = ft_strchr(set, str[i + size]);
        if (tmp != NULL)
            break ;
        size++;
    }
    if (tmp && stopped_at)
        *stopped_at = *tmp;
    else
        *stopped_at = '\0';
    size++;
    new_str = (char *)ft_calloc(size, sizeof(char));
    if (!new_str)
       return (NULL);
    ft_strlcpy(new_str, str + i, size);
    i += size;
    old_str = str;
    return (i++, new_str);
}
