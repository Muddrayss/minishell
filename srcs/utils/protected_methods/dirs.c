/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:39:25 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 21:11:16 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

DIR *opendir_p(char *path)
{
    DIR    *dir;

    dir = opendir(path);
    if (!dir && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (dir);
}

struct dirent   *readdir_p(DIR *dir)
{
    struct dirent    *entry;

    entry = readdir(dir);
    if (!entry && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (entry);
}

char   *getcwd_p(char *buf, size_t size)
{
    char    *cwd;

    cwd = getcwd(buf, size);
    if (!cwd && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (cwd);
}

int    chdir_p(char *path)
{
    int    ret;

    ret = chdir(path);
    if (ret == -1 && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (ret);
}