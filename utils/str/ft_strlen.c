/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:17 by craimond          #+#    #+#             */
/*   Updated: 2024/02/08 21:16:08 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

uint32_t     ft_strlen(char *str)
{
    uint32_t     i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}
