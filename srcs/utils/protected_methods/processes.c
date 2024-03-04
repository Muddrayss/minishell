/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:53 by craimond          #+#    #+#             */
/*   Updated: 2024/03/04 01:39:15 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void    pipe_p(int16_t *const fds)
{
    int32_t tmp[2];

    tmp[0] = fds[0];
    tmp[1] = fds[1];
    if (pipe(tmp) == -1)
        ft_quit(ERR_FD, NULL);
    fds[0] = tmp[0];
    fds[1] = tmp[1];
}

pid_t    fork_p(void)
{
    const pid_t pid = fork();

    if (pid == -1)
        ft_quit(ERR_FORK, NULL);
    return (pid);
}