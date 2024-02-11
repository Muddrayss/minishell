/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:41:04 by craimond          #+#    #+#             */
/*   Updated: 2024/02/05 12:02:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

size_t	ft_matrixsize(char **matrix)
{
    size_t	size;

    size = 0;
    if (!matrix)
        return (0);
    while (matrix[size])
        size++;
    return (size);
}