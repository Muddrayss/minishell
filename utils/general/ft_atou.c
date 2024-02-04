/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:59:54 by egualand          #+#    #+#             */
/*   Updated: 2024/02/04 16:59:57 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

unsigned int	ft_atou(char *nptr)
{
	size_t 	n;
	char	sign;

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
	if (n > UINT_MAX)
		return (UINT_MAX);
	return (n);
}