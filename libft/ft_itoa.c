/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:17:34 by egualand          #+#    #+#             */
/*   Updated: 2023/10/14 16:17:43 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int			i;
	long long	num;

	num = (long long)n;
	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	long long		num;
	int				n_len;
	int				i;
	int				j;

	i = 0;
	n_len = ft_count_digits(n);
	j = n_len - 1;
	num = (long long)n;
	str = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[i++] = '-';
		num *= -1;
	}
	while (i++ < n_len)
	{
		str[j--] = (char)((num % 10) + 48);
		num /= 10;
	}
	str[i - 1] = '\0';
	return (str);
}