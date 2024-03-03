/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:53 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 19:45:34 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void    pipe_p(int16_t *const fds)
{
    if (pipe((int32_t *)fds) == -1)
        ft_quit(ERR_FD, NULL);
}

pid_t    fork_p(void)
{
    const pid_t pid = fork();

    if (pid == -1)
        ft_quit(ERR_FORK, NULL);
    return (pid);
}