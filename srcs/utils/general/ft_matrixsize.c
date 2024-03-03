/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:41:04 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 16:32:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

uint16_t	ft_matrixsize(const char **const matrix)
{
    uint16_t	size;

    size = 0;
    if (!matrix)
        return (0);
    while (matrix[size])
        size++;
    return (size);
}