/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:25:10 by egualand          #+#    #+#             */
/*   Updated: 2023/10/19 14:25:16 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		start = s_len;
	if (len > (s_len - start))
		len = (s_len - start);
	if (start == s_len)
		sub = (char *)malloc(sizeof(char));
	else
		sub = (char *)malloc((sizeof(char) * len) + 1);
	if (sub == NULL)
		return (NULL);
	while (i < len && s[start] != '\0' && start < s_len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}