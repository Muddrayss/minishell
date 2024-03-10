/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:59:54 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static bool	is_space(t_cc c);

int32_t	ft_atoi(t_cc *nptr)
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

static bool	is_space(t_cc c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
