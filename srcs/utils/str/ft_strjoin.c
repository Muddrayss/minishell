/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:12:11 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 15:15:48 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*ft_strjoin(const char *s1, const char *s2, const uint8_t alloc_type)
{
	char		*newstr;
	uint16_t	i;
	uint16_t	n;

	i = 0;
	newstr = (char *)malloc_p(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1), alloc_type);
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	n = i;
	i = 0;
	while (s2[i] != '\0')
	{
		newstr[n + i] = s2[i];
		i++;
	}
	newstr[n + i] = '\0';
	return (newstr);
}
