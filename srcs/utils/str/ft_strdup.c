/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:52:49 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*ft_strdup(t_cc *const s, const uint8_t alloc_type)
{
	char			*dst;
	const uint16_t	len = ft_strlen(s);

	dst = (char *)malloc_p(sizeof(char) * (len + 1), alloc_type);
	ft_strlcpy(dst, s, len + 1);
	return (dst);
}
