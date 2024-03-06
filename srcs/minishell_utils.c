/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:25 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 21:35:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

char	*clear_quotes(const char *const str)
{
	uint32_t	i;
	uint32_t	j;
	char		*new_str;
	char		master_quote;

	if (!ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return ((char *)str);
	new_str = (char *)malloc_p(sizeof(char) * (ft_strlen(str) + 1), TMP);
	master_quote = '\0';
	j = 0;
	i = 0;
	while (str[i])
	{
		if (!master_quote && is_quote(str[i]))
			master_quote = str[i];
		else if (str[i] == master_quote)
			master_quote = '\0';
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
