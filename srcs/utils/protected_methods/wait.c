/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:38:07 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 23:48:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void    wait_p(int32_t *status)
{
    if (wait(status) == -1)
        ft_quit(ERR_WAIT, NULL);
}

void    waitpid_p(pid_t pid, int32_t *status, int32_t options)
{
    if (waitpid(pid, status, options) == -1)
        ft_quit(ERR_WAIT, NULL);
}