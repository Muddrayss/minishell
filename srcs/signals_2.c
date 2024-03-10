/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:23:16 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 16:24:22 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	interactive_mode(const int32_t signo)
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

void	heredoc_mode(const int32_t signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		release_resources();
		exit(130);
	}
	else if (signo == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

void	command_mode(const int32_t signo)
{
	if (signo == SIGINT)
	{
		g_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		release_resources();
		exit(130);
	}
	else if (signo == SIGQUIT)
	{
		g_status = 131;
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		release_resources();
		exit(131);
	}
}
