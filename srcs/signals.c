/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/02/20 16:03:22 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void silent_mode(int signo);
static void interactive_mode(int signo);
static void heredoc_mode(int signo);
static void command_mode(int signo);
static void death_mode(int signo);

void    set_signals(int8_t mode)
{
    int8_t  modes[4] = {S_SILENT, S_INTERACTIVE, S_HEREDOC, S_COMMAND};
    void    (*sig_handler[4])(int) = {&silent_mode, &interactive_mode, &heredoc_mode, &command_mode};
    int8_t  n_modes = sizeof(modes) / sizeof(modes[0]);
    
    while (n_modes--)
        if (modes[n_modes] == mode)
            break; 
    if (n_modes < 0)
    {
        ft_putstr_fd("Internal error: invalid signal mode\n", STDERR_FILENO);
        return;
    }
    signal_p(SIGINT, sig_handler[n_modes]);
    signal_p(SIGQUIT, sig_handler[n_modes]);
}

void    set_death_mode(void)
{
    signal_p(SIGUSR1, &death_mode);
    signal_p(SIGUSR2, &death_mode);
    signal_p(SIGTERM, SIG_IGN);
}

static void death_mode(int signo)
{
    static int  id
    = 0;
    static int n_signals
    = 0;

    if (signo == SIGUSR1)
        id |= 0x01 << n_signals++;
    else if (signo == SIGUSR2)
        n_signals++;
    if (n_signals == sizeof(id))
    {
        kill(-(get_data()->main_pid), SIGTERM);
        exit(id);
    }
}

static void silent_mode(int signo)
{
    if (signo == SIGINT)
        g_status = 130;
    else if (signo == SIGQUIT)
        g_status = 131;
}

static void interactive_mode(int signo)
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

static void heredoc_mode(int signo)
{
    if (signo == SIGINT)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        exit(130);
    }
    else if (signo == SIGQUIT)
        ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

static void command_mode(int signo)
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

