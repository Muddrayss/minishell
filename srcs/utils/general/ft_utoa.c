/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:02:38 by craimond          #+#    #+#             */
/*   Updated: 2024/02/12 00:07:58 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	nbr_len(long n);

char	*ft_utoa(unsigned int n)
{
	char	*str;
	int		n_len;
	long	n_long;

	n_long = n;
	n_len = nbr_len(n_long);
	str = malloc((n_len + 1) * sizeof(char));
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

static int	nbr_len(long n)
{
	int	i;

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