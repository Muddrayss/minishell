/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:10:36 by egualand          #+#    #+#             */
/*   Updated: 2023/10/14 15:44:26 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	pos;
	unsigned int	i;

	if (!*little)
		return ((char *)big);
	pos = 0;
	while (big[pos] != '\0' && (size_t)pos < len)
	{
		if (big[pos] == little[0])
		{
			i = 1;
			while (little[i] != '\0' && big[pos + i] == little[i]
				&& (size_t)(pos + i) < len)
				++i;
			if (little[i] == '\0')
				return ((char *)&big[pos]);
		}
		pos++;
	}
	return (0);
}