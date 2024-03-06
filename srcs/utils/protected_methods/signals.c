/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:38:42 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 21:11:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	signal_p(const int32_t signo, const __sighandler_t handler)
{
	if (signal(signo, handler) == SIG_ERR)
		panic(ERR_SIGSETUP, NULL);
}

void	sigaction_p(const int32_t signo, const struct sigaction *act, struct sigaction *oldact)
{
	if (sigaction(signo, act, oldact) == -1)
		panic(ERR_SIGSETUP, NULL);
}
