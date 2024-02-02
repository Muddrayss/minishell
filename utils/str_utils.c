/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:24:23 by craimond          #+#    #+#             */
/*   Updated: 2024/02/02 14:14:47 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**fill_matrix(int n_words, const char *s, char c, char **str_array);
static void free_matrix(char **str_array);

int     ft_strlen(char *str)
{
    int     i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

void   ft_putstr_fd(char *s, int fd)
{
    write(fd, s, ft_strlen(s));
}

char	**ft_split(const char *s, char c)
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

static char	**fill_matrix(int n_words, const char *s, char c, char **str_array)
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
			return (free_matrix(str_array), NULL);
		str_array[g][len++] = '\0';
		i = len - 1;
		while (--len > 0)
			str_array[g][len - 1] = s[len - 1];
		s += i;
	}
	return (str_array);
}

static char	**free_matrix(char **str_array, int g)
{
    int i;

    i = -1;
	while (str_array && str_array[++g])
		free(str_array[g]);
	free(str_array);
}

