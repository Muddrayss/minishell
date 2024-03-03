/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:23 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 19:45:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

uint16_t    open_p(const char *const path, const int32_t flags, const uint16_t mode)
{
    const int16_t   fd = open(path, flags, mode);

    if (fd == -1)
        ft_quit(ERR_FD, NULL);
    return ((uint16_t)fd);
}

void    close_p(const int16_t fd)
{
    if (close(fd) == -1)
        ft_quit(ERR_FD, NULL);
}

void    reset_fd(int16_t *const fd)
{
    if (*fd >= 0)
        close_p(*fd);
    *fd = -42;
}