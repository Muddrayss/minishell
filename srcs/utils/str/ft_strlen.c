/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:17 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 00:12:13 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

uint16_t    ft_strlen(const char *str)
{
    uint16_t    i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}
