/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:23 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 13:53:30 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int    open_p(char *path, int flags, uint16_t permissions)
{
    int    fd;

    fd = open(path, flags, permissions);
    if (fd == -1)
        ft_quit(ERR_FD, NULL);
    return (fd);
}

void    close_p(int fd)
{
    if (close(fd) == -1)
        ft_quit(ERR_FD, NULL);
}

void    reset_fd(int *fd)
{
    if (*fd >= 0)
        close_p(*fd);
    *fd = -42;
}