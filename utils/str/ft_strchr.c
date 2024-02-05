/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:45:36 by craimond          #+#    #+#             */
/*   Updated: 2024/02/05 12:00:31 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strchr( char *s, int c)
{
    while (*s && *s != c)
        s++;
    if (*s == c)
        return ((char *)s);
    return (NULL);
}