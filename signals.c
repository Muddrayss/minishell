/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/01/29 18:03:08 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

//TODO not yet done

static void	sig_handler(int signo)
{
	errno = EINTR;
	if (signo == SIGINT)
	{
		g_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		g_status = 131;
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
}

static void	in_cmd_sig_handler(int signo)
{
	errno = EINTR;
	if (signo == SIGINT)
	{
		g_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		// rl_on_new_line();
		// rl_replace_line("", STDIN_FILENO);
		// rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		g_status = 131;
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

void	init_signals(void)
{
	return ;
	if (signal(SIGINT, &sig_handler) == SIG_ERR)
		ft_quit(SIGINT_ERROR, "Signal error.");
	if (signal(SIGQUIT, &sig_handler) == SIG_ERR)
		ft_quit(SIGQUIT_ERROR, "Signal error.");
}

void	init_in_cmd_signals(void)
{
	return ;
	if (signal(SIGINT, &in_cmd_sig_handler) == SIG_ERR)
		ft_quit(SIGINT_ERROR, "Signal error.");
	if (signal(SIGQUIT, &in_cmd_sig_handler) == SIG_ERR)
		ft_quit(SIGQUIT_ERROR, "Signal error.");
}