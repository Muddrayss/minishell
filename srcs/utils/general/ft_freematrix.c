/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:21:37 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 15:01:59 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	ft_freematrix(char **matrix)
{
    char    **tmp;

    if (!matrix)
        return ;
    tmp = matrix;
    while (*tmp)
    {
        free_and_null((void **)tmp);
        tmp++;
    }
    free_and_null((void **)&matrix);
}