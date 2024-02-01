/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:37:20 by marvin            #+#    #+#             */
/*   Updated: 2024/02/01 16:30:57 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void    set_sighandler(void *handle_sigint, void *handle_sigquit) //int flags da shiftare
{
    if (signal(SIGINT, handle_sigint) == SIG_ERR)
        ft_quit(25, NULL);
    if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
        ft_quit(26, NULL);
}

//TODO da gestire ctrl+'\' in interactive mode che deve fare il core dump

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

void    hide_signal(int signo) //O_HIDE
{
    g_status = signo;
    ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

// void interactive_mode(int signo)
// {
//     if (signo == SIGINT)
//     {
//         g_status = 130;
//         ft_putstr_fd("\n", STDOUT_FILENO);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
//     else if (signo == SIGQUIT)
// 	{
//         g_status = 131;
//         ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
//     }
// }

// void heredoc_mode(int signo)
// {
//     if (signo == SIGINT)
//     {
// 		ft_putstr_fd("\b\b  \b\b\n", STDOUT_FILENO);
//         exit(130);
//     }
//    	else if (signo == SIGQUIT)
// 	{
// 		g_status = 131;
// 		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
// 	}
// }
