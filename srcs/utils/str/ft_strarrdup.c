/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:31:11 by craimond          #+#    #+#             */
/*   Updated: 2024/02/21 15:52:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	**ft_strarrdup(char **arr)
{
    char	    **new_arr;
    uint32_t	size;
    uint32_t	i;
    uint32_t    j;

    size = 0;
    j = -1;
    while (arr && arr[++j])
        size += ft_strlen(arr[j]) + 1;
    new_arr = (char **)malloc(sizeof(char *) * (size + 1));
    if (!new_arr)
        return (NULL);
    i = 0;
    while (arr && arr[i])
    {
        new_arr[i] = ft_strdup(arr[i]);
        if (!new_arr[i])
        {
            ft_freematrix(new_arr);
            return (NULL);
        }
        i++;
    }
    new_arr[i] = NULL;
    return (new_arr);
}