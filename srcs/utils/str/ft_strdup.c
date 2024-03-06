/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:52:49 by egualand          #+#    #+#             */
/*   Updated: 2024/03/06 15:42:17 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*ft_strdup(const char *const s, const uint8_t alloc_type)
{
	char			*dst;
	const uint16_t	len = ft_strlen(s);

	dst = (char *)malloc_p(sizeof(char) * (len + 1), alloc_type);
	ft_strlcpy(dst, s, len + 1);
	return (dst);
}
