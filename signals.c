/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/02/02 17:28:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void    set_sighandler(void *handle_sigint, void *handle_sigquit) //int8_t flags da shiftare
{
    signal_p(SIGINT, handle_sigint);
    signal_p(SIGQUIT, handle_sigquit);
}

//TODO dopo ctr+c in heredoc si rompe tutto


//per queste 3 funzioni sarebbe figo fare lo shift dei bit come in open
//rendere quindi queste statiche e scegliere quale chiamare in base alla flag nel set_sighandler
void    display_signal(int signo) //O_DISPLAY
{
    g_status = signo;
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    display_and_quit_signal(int signo) //O_DQUIT
{
    g_status = signo;
    ft_putstr_fd("\n", STDOUT_FILENO);
    exit(signo);
}

void    hide_and_abort_signal(int signo) //O_DCORE
{
    g_status = signo;
    ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO); //non identico a bash ma pie' bello
    ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
    exit(signo);
}

void newline_signal(int signo)
{
    (void)signo;
    ft_putstr_fd("\n", STDOUT_FILENO);
}
