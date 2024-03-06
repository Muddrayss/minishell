/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:04:47 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 15:37:00 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	ft_bzero(void *s, size_t n);

void	*ft_calloc(const size_t nmemb, const size_t size)
{
	void	*arr;

	if (nmemb != 0 && size > ULONG_MAX / nmemb)
		return (NULL);
	arr = (void *)malloc(size * nmemb);
	if (!arr)
		return (NULL);
	ft_bzero(arr, size * nmemb);
	return (arr);
}

void	ft_bzero(void *const s, size_t n)
{
	char *const	ptr = (char *)s;

	while (n-- > 0)
		ptr[n] = '\0';
}
