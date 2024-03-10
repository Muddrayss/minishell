/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/03/10 16:24:32 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	silent_mode(const int32_t signo);
static void	catch_panic(const int32_t signo,
				siginfo_t *const info, void *const context);
static void	safe_exit(const int32_t signo);

void	set_signals(const uint8_t mode, const bool is_main)
{
	static const __sighandler_t	sig_handler[]
		= {&interactive_mode, &heredoc_mode, &command_mode, &silent_mode};

	signal_p(SIGINT, sig_handler[mode]);
	signal_p(SIGQUIT, sig_handler[mode]);
	if (!is_main)
		signal_p(SIGTERM, &safe_exit);
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &catch_panic;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction_p(SIGUSR1, &sa, NULL);
	sigaction_p(SIGUSR2, &sa, NULL);
}

static void	safe_exit(const int32_t signo)
{
	(void)signo;
	release_resources();
	exit(0);
}

static void	catch_panic(const int32_t signo,
	siginfo_t *const info, void *const context)
{
	static pid_t	calling_pid = -1;
	static uint8_t	id = 0;
	static uint8_t	n_signals = 0;

	(void)context;
	if (calling_pid == -1)
		calling_pid = info->si_pid;
	else if (calling_pid != info->si_pid)
		return ;
	if (signo == SIGUSR1)
		id |= 0x01 << n_signals++;
	else if (signo == SIGUSR2)
		n_signals++;
	if (n_signals == (sizeof(id) * 8))
	{
		signal_p(SIGTERM, SIG_IGN);
		kill(-get_data()->main_pid, SIGTERM);
		signal_p(SIGTERM, &safe_exit);
		release_resources();
		while (waitpid(-1, NULL, WNOHANG) > 0)
			;
		exit(id);
	}
}

static void	silent_mode(const int32_t signo)
{
	if (signo == SIGINT)
		g_status = 130;
	else if (signo == SIGQUIT)
		g_status = 131;
}
