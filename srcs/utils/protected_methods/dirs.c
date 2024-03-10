/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:39:25 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 14:50:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

DIR	*opendir_p(t_cc *const name)
{
	const DIR *const	dir = opendir(name);

	if (!dir && is_bad_errno(errno))
		panic(ERR_MEM, NULL);
	return ((DIR *)dir);
}

struct dirent	*readdir_p(const DIR *const dir)
{
	const struct dirent *const	entry = readdir((DIR *)dir);

	if (!entry && is_bad_errno(errno))
		panic(ERR_MEM, NULL);
	return ((struct dirent *)entry);
}

char	*getcwd_p(t_cc *const buf, const size_t size, const uint8_t alloc_type)
{
	t_cc *const	cwd = getcwd((char *)buf, size);

	if (!cwd && is_bad_errno(errno))
		panic(ERR_MEM, NULL);
	if (alloc_type == TMP)
		gc_add(cwd);
	return ((char *)cwd);
}

int32_t	chdir_p(t_cc *const path)
{
	const int32_t	ret = chdir(path);

	if (ret == -1 && is_bad_errno(errno))
		panic(ERR_MEM, NULL);
	return (ret);
}
