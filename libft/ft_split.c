/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:39:07 by egualand          #+#    #+#             */
/*   Updated: 2024/01/29 22:00:32 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_arr(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	in_arr;

	i = 0;
	count = 0;
	in_arr = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && in_arr == 0)
		{
			count++;
			in_arr = 1;
		}
		else if (s[i] == c)
			in_arr = 0;
		i++;
	}
	return (count);
}

static char	*ft_make_string(char const *s, size_t start, char c)
{
	char	*division;
	size_t	i;
	size_t	j;
	size_t	str_len;

	i = 0;
	j = start;
	str_len = 0;
	if (s[i] == '\0' || s == 0)
		return (NULL);
	while (s[j] != c && s[j])
	{
		j++;
		str_len++;
	}
	division = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (division == NULL)
		return (NULL);
	while (i < str_len)
		division[i++] = s[start++];
	division[i] = '\0';
	return (division);
}

static char	**ft_make_split(char **array, char const *s, char c)
{
	int	i;
	int	in_arr;
	int	arr_index;

	i = -1;
	in_arr = 0;
	arr_index = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c && in_arr == 0)
		{
			array[arr_index++] = ft_make_string(s, i, c);
			if (array[arr_index - 1] == NULL)
				return (ft_free_matrix(array), NULL);
			in_arr = 1;
		}
		else if (s[i] == c)
			in_arr = 0;
	}
	array[arr_index] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	array = (char **)ft_calloc(ft_count_arr(s, c) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = ft_make_split(array, s, c);
	if (array == NULL)
		return (NULL);
	else
		return (array);
}
