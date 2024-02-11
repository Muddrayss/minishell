/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:52:49 by egualand          #+#    #+#             */
/*   Updated: 2024/02/11 22:23:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strdup(char *s)
{
	char	*dst;
	int		i;

	if (!s)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s) + 3));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}