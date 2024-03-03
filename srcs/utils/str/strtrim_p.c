/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:36:23 by egualand          #+#    #+#             */
/*   Updated: 2024/03/03 16:54:04 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*strtrim_p(const char *s1, const char *const set)
{
	char		*newstr;
	char		*start;
	uint16_t	i;

	start = (char *)s1;
	i = 0;
	while (*s1 != '\0' && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i > 0 && ft_strchr(set, s1[i - 1]))
		i--;
	newstr = (char *)malloc_p(sizeof(char) * (i + 1));
	if (newstr == NULL)
		return (free_and_null((void **)&start), NULL);
	newstr[i] = '\0';
	while (i > 0)
	{
		newstr[i - 1] = s1[i - 1];
		i--;
	}
	return (free_and_null((void **)&start), newstr);
}
