/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:21:37 by craimond          #+#    #+#             */
/*   Updated: 2024/02/21 15:20:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	ft_freematrix(char **matrix)
{
    unsigned int	i;

    if (!matrix)
        return ;
    i = 0;
    while (matrix[i])
        free(matrix[i++]);
    free(matrix);
}