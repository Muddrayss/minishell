/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:02:38 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 14:37:08 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static uint8_t	nbr_len(long n);

char	*ft_itoa(int32_t n)
{
	int64_t		n_long;
	char		*str;
	uint8_t		n_len;

	n_long = n;
	n_len = nbr_len(n_long);
	str = (char *)malloc((n_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n_long == 0)
		str[0] = '0';
	str[n_len] = '\0';
	while (n_long > 0)
	{
		str[n_len-- - 1] = (n_long % 10) + 48;
		n_long /= 10;
	}
	return (str);
}

static uint8_t	nbr_len(int64_t n)
{
	uint8_t	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}