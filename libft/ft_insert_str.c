/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:51:55 by craimond          #+#    #+#             */
/*   Updated: 2024/01/30 14:54:15 by egualand         ###   ########.fr       */
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
