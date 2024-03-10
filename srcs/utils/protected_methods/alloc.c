/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:40:05 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:13:04 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	*malloc_p(const size_t size, const uint8_t alloc_type)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		panic(ERR_MEM, "minishell: failed to allocate memory");
	if (alloc_type == TMP)
		gc_add(ptr);
	return (ptr);
}

void	*calloc_p(const size_t nmemb,
	const size_t size, const uint8_t alloc_type)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		panic(ERR_MEM, "minishell: failed to allocate memory");
	if (alloc_type == TMP)
		gc_add(ptr);
	return (ptr);
}
