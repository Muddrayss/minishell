/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:34:03 by craimond          #+#    #+#             */
/*   Updated: 2024/02/18 16:23:00 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	**fill_matrix(int n_words, char *s, char c, char **str_array);

char	**ft_split(char *s, char c)
{
	int		n_words;
	int		i;
	char	**str_array;

	if (s == NULL || *s == '\0')
	{
		str_array = ft_calloc(sizeof(char *), 1);
		if (str_array == NULL)
			return (NULL);
		return (str_array);
	}
	i = -1;
	n_words = 0;
	if (s[0] != c && s[0] != '\0')
		n_words++;
	while (s[++i + 1] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			n_words++;
	}
	str_array = malloc(sizeof(char *) * (n_words + 1));
	if (str_array == NULL)
		return (NULL);
	str_array[n_words] = NULL;
	return (fill_matrix(n_words, s, c, str_array));
}

static char	**fill_matrix(int n_words, char *s, char c, char **str_array)
{
	int	g;
	int	i;
	int	len;

	g = -1;
	i = 0;
	len = 0;
	while (++g < n_words)
	{
		while (*s == c)
			s++;
		while (s[len] != c && s[len] != '\0')
			len++;
		str_array[g] = malloc(sizeof(char) * (len + 1));
		if (str_array[g] == NULL)
			return (ft_freematrix(str_array), NULL);
		str_array[g][len++] = '\0';
		i = len - 1;
		while (--len > 0)
			str_array[g][len - 1] = s[len - 1];
		s += i;
	}
	return (str_array);
}
