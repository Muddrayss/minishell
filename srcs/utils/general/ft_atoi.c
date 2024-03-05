/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:59:54 by egualand          #+#    #+#             */
/*   Updated: 2024/03/05 17:20:59 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static bool	is_space(const char c);

int32_t	ft_atoi(const char *nptr)
{
	int64_t		n;
	char		sign;

	n = 0;
	while (is_space(*nptr))
		nptr++;
	sign = nptr[0];
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr != '\0' && is_digit(*nptr))
	{
		n *= 10;
		n += (*nptr - 48);
		nptr++;
	}
	n = (-n) * (sign == '-') + (n) * (sign != '-');
	if (n > INT32_MAX)
		return (INT32_MAX);
	if (n < INT32_MIN)
		return (INT32_MIN);
	return ((int32_t)n);
}

static bool	is_space(const char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
