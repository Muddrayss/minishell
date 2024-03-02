/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:59:54 by egualand          #+#    #+#             */
/*   Updated: 2024/03/02 23:37:14 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int32_t	ft_atoi(char *nptr)
{
	int64_t 	n;
	char		sign;

	n = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	sign = nptr[0];
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr != '\0' && *nptr <= '9' && *nptr >= '0')
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
