/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:19:51 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

uint8_t	g_status;

static void	minishell_loop(void);

int	main(const int argc, t_cc **const argv, t_cc **const envp)
{
	check_args(argc, argv, envp);
	init_signals();
	init_data(envp);
	init_general();
	minishell_loop();
}

static void	minishell_loop(void)
{
	char				*input;
	static const char	prompt[]
		= RED "mi" YELLOW "ni" GREEN "sh" CYAN "el" PURPLE "l$ " DEFAULT;

	while (true)
	{
		set_signals(S_INTERACTIVE, true);
		input = readline(prompt);
		if (!input)
			panic(123, "exit");
		add_history(input);
		input = ft_strtrim(input, g_shell_spaces, TMP);
		if (!input)
			continue ;
		set_signals(S_SILENT, true);
		executor(parser(lexer(input)));
		gc_cleanup();
	}
}
