/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:05:57 by craimond          #+#    #+#             */
/*   Updated: 2024/02/22 16:11:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int  ft_strcmp_lower(const char *s1, const char *s2)
{
    char   first_lower;
    char   second_lower;

    while (*s1 && *s2)
    {
        first_lower = ft_tolower(*s1);
        second_lower = ft_tolower(*s2);
        if (first_lower != second_lower)
            return (first_lower - second_lower);
        s1++;
        s2++;
    }
    return (first_lower - second_lower);
}