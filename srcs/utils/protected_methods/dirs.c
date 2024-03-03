/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:39:25 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 16:54:04 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

DIR *opendir_p(const char *const name)
{
    DIR    *dir;

    dir = opendir(name);
    if (!dir && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (dir);
}

struct dirent   *readdir_p(const DIR *const dir)
{
    struct dirent    *entry;

    entry = readdir((DIR *)dir);
    if (!entry && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (entry);
}

char   *getcwd_p(const char *const buf, const size_t size)
{
    char    *cwd;

    cwd = getcwd((char *)buf, size);
    if (!cwd && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (cwd);
}

int32_t    chdir_p(const char *const path)
{
    int32_t    ret;

    ret = chdir(path);
    if (ret == -1 && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (ret);
}