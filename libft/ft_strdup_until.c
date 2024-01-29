/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:16:31 by craimond          #+#    #+#             */
/*   Updated: 2024/01/29 21:53:02 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strdup_until(char *str, char c)
{
    char                    *new_str;
    static char             *old_str = NULL;
    size_t                  size;
    static unsigned int     i = 0;

    if (old_str != str)
        i = 0;
    size = 0;
    while (str[i + size] && str[i + size] != c)
        size++;
    size++;
    new_str = (char *)ft_calloc(size, sizeof(char));
    if (!new_str)
       return (NULL);
    ft_strlcpy(new_str, str + i, size);
    i += size;
    old_str = str;
    return (i++, new_str);
}