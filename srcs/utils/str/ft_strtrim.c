/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:36:23 by egualand          #+#    #+#             */
/*   Updated: 2024/03/06 11:18:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*ft_strtrim(const char *s1, const char *const set)
{
	char		*newstr;
	uint16_t	i;

	if (!set || !s1)
		return ((char *)s1);
	i = 0;
	while (*s1 != '\0' && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i > 0 && ft_strchr(set, s1[i - 1]))
		i--;
	newstr = (char *)malloc(sizeof(char) * (i + 1));
	if (!newstr)
		return (NULL);
	newstr[i] = '\0';
	while (i > 0)
	{
		newstr[i - 1] = s1[i - 1];
		i--;
	}
	return (newstr);
}
