/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/03/04 17:04:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

uint8_t	g_status;

static void minishell_loop(void);

int	main(const int argc, const char **const argv, const char **const envp)
{
	check_args(argc, argv, envp);
	init_data(envp);
	init_general();
	minishell_loop();
}

static void	minishell_loop()
{
	t_data 		*data;

	data = get_data();
	while (true)
	{
		//TODO gestire linea lunga che supera colonne
		set_signals(S_INTERACTIVE, true);
		free_and_null((void **)&data->input);
		data->input = readline(RED "mi" YELLOW "ni" GREEN "sh" CYAN "el" PURPLE "l$ " DEFAULT);
		if (!data->input)
			ft_quit(123, "exit");
		add_history(data->input);
		data->input = strtrim_p(data->input, " \t\n");
		if (!data->input)
			continue ;
		lexer(data->input);
		parser(data->lexered_params);
		lstclear(&data->lexered_params, &del_content_lexer);
		if (!data->parsed_params)
			continue ;
		set_signals(S_SILENT, true);
		executor(data->parsed_params);
		treeclear(&data->parsed_params, &del_content_parser);
	}
}


