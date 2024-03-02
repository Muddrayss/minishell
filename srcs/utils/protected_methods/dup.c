/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:37:10 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 23:45:21 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

uint16_t    dup_p(uint16_t fd)
{
    int32_t    newfd;

    newfd = dup(fd);
    if (newfd == -1)
        ft_quit(ERR_FD, NULL);
    return ((uint16_t)newfd);
}

void    dup2_p(uint16_t oldfd, uint16_t newfd)
{
    if (dup2(oldfd, newfd) == -1)
        ft_quit(ERR_FD, NULL);
}