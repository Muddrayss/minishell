/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:38:07 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 13:53:50 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void    wait_p(int *status)
{
    if (wait(status) == -1)
        ft_quit(ERR_WAIT, NULL);
}

void    waitpid_p(pid_t pid, int *status, int options)
{
    if (waitpid(pid, status, options) == -1)
        ft_quit(ERR_WAIT, NULL);
}