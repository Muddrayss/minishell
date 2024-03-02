/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:23 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 00:20:13 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

uint16_t    open_p(char *path, int32_t flags, uint16_t permissions)
{
    int16_t fd;

    fd = open(path, flags, permissions);
    if (fd == -1)
        ft_quit(ERR_FD, NULL);
    return ((uint16_t)fd);
}

void    close_p(int16_t fd)
{
    if (close(fd) == -1)
        ft_quit(ERR_FD, NULL);
}

void    reset_fd(int16_t *fd)
{
    if (*fd >= 0)
        close_p(*fd);
    *fd = -42;
}