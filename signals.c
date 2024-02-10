/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/02/10 17:58:29 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

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
        g_status = 130;
        ft_putstr_fd("\n", STDOUT_FILENO);
        exit(signo);  
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

void    set_signals(int mode)
{
    if (mode == S_SILENT)
    {
        signal(SIGINT, silent_mode);
        signal(SIGQUIT, silent_mode);
    }
    else if (mode == S_INTERACTIVE)
    {
        signal(SIGINT, interactive_mode);
        signal(SIGQUIT, interactive_mode);
    }
    else if (mode == S_HEREDOC)
    {
        signal(SIGINT, heredoc_mode);
        signal(SIGQUIT, heredoc_mode);
    }
    else if (mode == S_COMMAND)
    {
        signal(SIGINT, command_mode);
        signal(SIGQUIT, command_mode);
    }
    else
        ft_putstr_fd("Internal error: invalid signal mode\n", STDERR_FILENO);
}
