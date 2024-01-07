/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <egualand@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/01/07 18:51:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
	}
}

void init_signals(void)
{
	if (signal(SIGINT, &sig_handler) == SIG_ERR)
		ft_quit(SIGINT_ERROR, "Signal error.");
	// TODO: Capire se è necessario gestire SIGQUIT (Ctrl + \) oppure ignorarlo con SIG_IGN
	// SIGQUIT performa un core dump del processo.
	if (signal(SIGQUIT, &sig_handler) == SIG_ERR)
		ft_quit(SIGQUIT_ERROR, "Signal error.");
}