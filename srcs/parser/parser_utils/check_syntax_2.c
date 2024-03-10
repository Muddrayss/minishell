/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:00:20 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 16:00:43 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

uint8_t	check_redir_streak(t_cc *const cmd_str)
{
	uint16_t	i;

	i = 0;
	while (cmd_str[i] && is_redir(cmd_str[i]))
		i++;
	return (i > 2);
}

uint8_t	check_redir_pair(t_cc *const cmd_str)
{
	return (is_redir(cmd_str[1]) && cmd_str[0] != cmd_str[1]);
}

uint8_t	check_filename_presence(t_cc *const cmd_str)
{
	return (is_empty_str(clear_quotes(cmd_str + 1)));
}

void	tse(t_cc token)
{
	ft_putstr_fd("Syntax error near unexpected token: '", STDERR_FILENO);
	write(STDERR_FILENO, &token, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
