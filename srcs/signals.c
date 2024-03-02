/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/03/03 00:39:53 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void silent_mode(int32_t signo);
static void interactive_mode(int32_t signo);
static void heredoc_mode(int32_t signo);
static void command_mode(int32_t signo);
static void death_mode(int32_t signo, siginfo_t *info, void *context);
static void safe_exit(int32_t signo);

void    set_signals(uint8_t mode, bool is_main)
{
    struct sigaction    sa;
    __sighandler_t      sig_handler[] = {&interactive_mode, &heredoc_mode, &command_mode, &silent_mode}; //order has to be the same as the defines in the header file

    signal_p(SIGINT, sig_handler[mode]);
    signal_p(SIGQUIT, sig_handler[mode]);
    if (!is_main)
        signal_p(SIGTERM, &safe_exit);
    else
    {
        signal_p(SIGTERM, SIG_IGN);
        sa.sa_sigaction = death_mode;
        sa.sa_flags = SA_SIGINFO | SA_RESTART;
        sigemptyset(&sa.sa_mask);
        sigaction_p(SIGUSR1, &sa, NULL);
        sigaction_p(SIGUSR2, &sa, NULL);
    }
}

static void safe_exit(int32_t signo)
{
    (void)signo;
    free_data();
    exit(0);
}

static void death_mode(int32_t signo, siginfo_t *info, void *context)
{
    static uint8_t  id
    = 0;
    static uint8_t  n_signals
    = 0;
    static pid_t   pid
    = -1;

    (void)context;
    if (pid == -1)
        pid = info->si_pid;
    else if (pid != info->si_pid)
        return ;
    if (signo == SIGUSR1)
        id |= 0x01 << n_signals++;
    else if (signo == SIGUSR2)
        n_signals++;
    if (n_signals == (sizeof(id) * 8))
    {
        kill(-(get_data()->main_pid), SIGTERM);
        free_data();
        exit(id);
    }
}

static void silent_mode(int32_t signo)
{
    if (signo == SIGINT)
        g_status = 130;
    else if (signo == SIGQUIT)
        g_status = 131;
}

static void interactive_mode(int32_t signo)
{
    if (signo == SIGINT)
    {
        g_status = 130;
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signo == SIGQUIT)
        ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

static void heredoc_mode(int32_t signo)
{
    if (signo == SIGINT)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        exit(130);
    }
    else if (signo == SIGQUIT)
        ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

static void command_mode(int32_t signo)
{
    if (signo == SIGINT)
    {
        g_status = 130;
        ft_putstr_fd("\n", STDOUT_FILENO);
        exit(130);  
    }
    else if (signo == SIGQUIT)
    {
        g_status = 131;
        ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO); //non identico a bash ma pie' bello
        ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
        exit(131);
    }
}

