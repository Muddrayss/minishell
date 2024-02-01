/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/02/01 13:35:28 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void sig_handler_interactive_mode(int signo) {
    if (signo == SIGINT) {
        g_status = 130;
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    } else if (signo == SIGQUIT)
	{
        g_status = 131;
        ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO); // Erase "^\" from terminal
    }
}

static void sig_handler_heredoc(int signo) {
    if (signo == SIGINT) {
        g_status = 130;
      	ft_putstr_fd("\n", STDOUT_FILENO);
		rl_done = 1;
    }
   	else if (signo == SIGQUIT)
	{
		g_status = 131;
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
}

void set_interactive_mode(void)
{
	// rl_catch_signals = 1;
    if (signal(SIGINT, sig_handler_interactive_mode) == SIG_ERR)
        ft_quit(SIGINT_ERROR, "Signal error.");
    if (signal(SIGQUIT, sig_handler_interactive_mode) == SIG_ERR)
        ft_quit(SIGQUIT_ERROR, "Signal error.");
}

void set_heredoc_mode(void)
{
    // rl_catch_signals = 0;
    if (signal(SIGINT, sig_handler_heredoc) == SIG_ERR)
        ft_quit(SIGINT_ERROR, "Signal error.");
    if (signal(SIGQUIT, sig_handler_heredoc) == SIG_ERR)
        ft_quit(SIGQUIT_ERROR, "Signal error.");
}

void set_default_mode(void)
{
    // rl_catch_signals = 1;
    if (signal(SIGINT, SIG_DFL) == SIG_ERR)
        ft_quit(SIGINT_ERROR, "Signal error.");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        ft_quit(SIGQUIT_ERROR, "Signal error.");
}