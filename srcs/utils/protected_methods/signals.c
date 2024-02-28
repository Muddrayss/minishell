/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:38:42 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 13:53:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void    signal_p(int signum, void (*handler)(int))
{
    if (signal(signum, handler) == SIG_ERR)
        ft_quit(ERR_SIGSETUP, NULL);
}

void    sigaction_p(int signum, struct sigaction *act, struct sigaction *oldact)
{
    if (sigaction(signum, act, oldact) == -1)
        ft_quit(ERR_SIGSETUP, NULL);
}