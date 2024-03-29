/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:39:25 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 21:11:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

DIR	*opendir_p(const char *const name)
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

char	*getcwd_p(const char *const buf, const size_t size, const uint8_t alloc_type)
{
	const char *const	cwd = getcwd((char *)buf, size);

	if (!cwd && is_bad_errno(errno))
		panic(ERR_MEM, NULL);
	if (alloc_type == TMP)
		gc_add(cwd);
	return ((char *)cwd);
}

int32_t	chdir_p(const char *const path)
{
	const int32_t	ret = chdir(path);

	if (ret == -1 && is_bad_errno(errno))
		panic(ERR_MEM, NULL);
	return (ret);
}
