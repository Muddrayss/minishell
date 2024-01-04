/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:53:47 by egualand          #+#    #+#             */
/*   Updated: 2023/10/14 13:53:53 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_l;
	size_t	src_l;

	i = ft_strlen(dst);
	dst_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	j = 0;
	if (size <= 0)
		return (src_l + size);
	while (src[j] != '\0' && i < (size - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (size < dst_l)
		return (src_l + size);
	else
		return (dst_l + src_l);
}
