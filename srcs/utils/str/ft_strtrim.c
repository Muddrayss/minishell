/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:36:23 by egualand          #+#    #+#             */
/*   Updated: 2024/03/01 18:20:10 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static bool	ft_cinstr(char *str, char c);

char	*ft_strtrim(char *s1, char *set)
{
	char	*newstr;
	char	*start;
	size_t	i;

	start = s1;
	i = 0;
	while (*s1 != '\0' && ft_cinstr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i > 0 && ft_cinstr(set, s1[i - 1]))
		i--;
	newstr = (char *)malloc(sizeof(char) * (i + 1));
	if (newstr == NULL)
		return (free(start), NULL);
	newstr[i] = '\0';
	while (i > 0)
	{
		newstr[i - 1] = s1[i - 1];
		i--;
	}
	return (free(start), newstr);
}

static bool	ft_cinstr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}