/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:05:57 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int16_t	ft_strcmp_lower(t_cc *s1, t_cc *s2)
{
	char	first_lower;
	char	second_lower;

	while (*s1 && *s2)
	{
		first_lower = ft_tolower(*s1);
		second_lower = ft_tolower(*s2);
		if (first_lower != second_lower)
			return (first_lower - second_lower);
		s1++;
		s2++;
	}
	return (first_lower - second_lower);
}
