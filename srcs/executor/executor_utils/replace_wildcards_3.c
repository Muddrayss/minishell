/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:00:38 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 15:08:23 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*add_cwd(t_cc *patn, t_cc *const cwd)
{
	char	*new_patn;

	if (patn[0] == '/')
		return ((char *)patn);
	new_patn = (char *)malloc_p(sizeof(char)
			* (ft_strlen(cwd) + ft_strlen(patn) + 2), TMP);
	ft_strcpy(new_patn, cwd);
	ft_strcat(new_patn, "/");
	ft_strcat(new_patn, patn);
	return (new_patn);
}

char	*insert_result(t_cc *const str, const t_list *const matching_files,
	const uint16_t idx, const uint16_t patn_len)
{
	t_list		*node;
	char		*new_str;
	uint16_t	size;
	uint16_t	filenames_len;

	if (!matching_files)
		return ((char *)str);
	node = (t_list *)matching_files;
	filenames_len = 0;
	while (node)
	{
		filenames_len += ft_strlen(node->content) + 1;
		node = node->next;
	}
	size = ft_strlen(str) - patn_len + filenames_len + 1;
	new_str = (char *)malloc_p(sizeof(char) * size, TMP);
	ft_strlcpy(new_str, str, idx + 1);
	node = (t_list *)matching_files;
	while (node)
	{
		ft_strcat(new_str, node->content);
		ft_strcat(new_str, " ");
		node = node->next;
	}
	return (ft_strcat(new_str, &str[idx + patn_len]), new_str);
}
