/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:36:23 by egualand          #+#    #+#             */
/*   Updated: 2024/02/18 17:24:14 by egualand         ###   ########.fr       */
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
	newstr = malloc(sizeof(char) * (i + 1));
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