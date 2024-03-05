/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 23:58:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

uint8_t	g_status;

static void	minishell_loop(void);

int	main(const int argc, const char **const argv, const char **const envp)
{
	check_args(argc, argv, envp);
	init_data(envp);
	init_general();
	minishell_loop();
}

static void	minishell_loop()
{
	char				*input;
	static const char	prompt[] = RED "mi" YELLOW "ni" GREEN "sh" CYAN "el" PURPLE "l$ " DEFAULT;

	while (true)
	{
		//TODO distinguish between temporary_data(resources-stack) and permanent_data(envp_matrix, envp_tree, starting_dir) 
		set_signals(S_INTERACTIVE, true);
		input = readline(prompt);
		if (!input)
			ft_quit(123, "exit");
		add_history(input);
		input = strtrim_p(input, g_shell_spaces);
		if (!input)
			continue ;
		set_signals(S_SILENT, true);
		executor(parser(lexer(input)));
	}
}
