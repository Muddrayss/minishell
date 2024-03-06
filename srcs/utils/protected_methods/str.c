/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:53:30 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 11:43:29 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*strdup_p(const char *const str)
{
	char	*new_str;

	new_str = ft_strdup(str);
	if (!new_str)
		ft_quit(ERR_MEM, "minishell: failed to allocate memory");
	lstadd_front(get_tmp_resources_stack(), lstnew(new_str, true));
	return (new_str);
}

char	*strjoin_p(const char *const s1, const char *const s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (!new_str)
		ft_quit(ERR_MEM, "minishell: failed to allocate memory");
	lstadd_front(get_tmp_resources_stack(), lstnew(new_str, true));
	return (new_str);
}

char    *strtrim_p(const char *const s1, const char *const set)
{
	char	*new_str;

	new_str = ft_strtrim(s1, set);
	if (!new_str)
		ft_quit(ERR_MEM, "minishell: failed to allocate memory");
	lstadd_front(get_tmp_resources_stack(), lstnew(new_str, true));
	return (new_str);
}