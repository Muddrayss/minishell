/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:08:46 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 20:09:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**ft_strarr_dup(char **arr)
{
    char	**dup;
    int		i;

    dup = malloc(sizeof(char *) * (ft_strarr_len(arr) + 1));
    i = -1;
    while (arr[++i])
        dup[i] = ft_strdup(arr[i]);
    dup[i] = NULL;
    return (dup);
}