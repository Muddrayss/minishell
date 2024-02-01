/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:51:55 by craimond          #+#    #+#             */
/*   Updated: 2024/02/01 14:32:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_insert_str(char *big, char *new, unsigned int start, unsigned int end)
{
    char            *new_str;
    unsigned int    size;

	if (start == end)
		return (big);
	if (!big)
		return (ft_strdup(new));
    size = ft_strlen(big) - (end - start) + ft_strlen(new) + 1;
    new_str = (char *)ft_calloc(size, sizeof(char));
    if (!new_str)
        return (NULL);
    ft_strlcat(new_str, big, start + 1);
    if (new[0] != '\0')
        ft_strlcat(new_str, new, size);
    ft_strlcat(new_str, big + end, size);
    return (free(big), new_str);
}
