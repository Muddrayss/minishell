/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:37:10 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 13:53:24 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int    dup_p(int fd)
{
    int    newfd;

    newfd = dup(fd);
    if (newfd == -1)
        ft_quit(ERR_FD, NULL);
    return (newfd);
}

void    dup2_p(int oldfd, int newfd)
{
    if (dup2(oldfd, newfd) == -1)
        ft_quit(ERR_FD, NULL);
}