/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrncpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:00:14 by craimond          #+#    #+#             */
/*   Updated: 2024/01/26 18:29:29 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_matrix(char **matrix);


char	**ft_strarrncpy(char **dst, char **src, size_t n)
{
    size_t	i;

    i = -1;
    while (++i < n)
    {
        dst[i] = ft_strdup(src[i]);
        if (!dst[i])
            return (free_matrix(dst), NULL);
    }
    return (dst);
}

static void	free_matrix(char **matrix)
{
    unsigned int	i;

    i = -1;
    while (matrix && matrix[++i])
        free(matrix[i]);
    free(matrix);
}