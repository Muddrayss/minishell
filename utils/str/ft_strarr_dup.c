/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:08:46 by craimond          #+#    #+#             */
/*   Updated: 2024/02/04 15:58:49 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**ft_strarr_dup(char **arr)
{
    char	**dup;
    int		i;

    dup = malloc(sizeof(char *) * (ft_strarr_len(arr) + 1));
    if (dup == NULL)
        return (NULL);
    i = -1;
    while (arr[++i])
    {
        dup[i] = ft_strdup(arr[i]);
        if (dup[i] == NULL)
            return (ft_freematrix(dup), NULL);
    }
    dup[i] = NULL;
    return (dup);
}