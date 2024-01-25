/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/01/25 16:51:38 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void	sig_handler(int signo)
{
	errno = EINTR;
	if (signo == SIGINT)
	{
		if (!g_signals.in_heredoc)
			ft_putstr_fd("\n", 2);
		if (g_signals.in_cmd)
		{
			g_signals.sigint = 1;
			rl_replace_line("", 0);
			rl_redisplay();
			rl_done = 1;
			return ;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
	}
}

void	init_signals(void)
{
	if (signal(SIGINT, &sig_handler) == SIG_ERR)
		ft_quit(SIGINT_ERROR, "Signal error.", NULL);
	if (signal(SIGQUIT, &sig_handler) == SIG_ERR)
		ft_quit(SIGQUIT_ERROR, "Signal error.", NULL);
}