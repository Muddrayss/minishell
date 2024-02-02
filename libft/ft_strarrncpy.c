/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrncpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:00:14 by craimond          #+#    #+#             */
/*   Updated: 2024/01/30 14:17:47 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrncpy(char **dst, char **src, size_t n)
{
    size_t	i;

    i = -1;
    while (++i < n)
    {
        dst[i] = ft_strdup(src[i]);
        if (!dst[i])
            return (ft_free_matrix(dst), NULL);
    }
    return (dst);
}