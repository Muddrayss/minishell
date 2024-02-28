/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 20:37:14 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_status;

static void minishell_loop(void);

int	main(int argc, char **argv, char **envp)
{
	check_args(argc, argv, envp);
	init_data(envp);
	init_general();
	minishell_loop();
}

static void	minishell_loop()
{
	t_data 		*data;
	t_list		*lexered_params;
	t_tree		*parsed_params;

	data = get_data();
	while (true)
	{
		//TODO gestire linea lunga che supera colonne
		set_signals(S_INTERACTIVE, true);
		free(data->input);
		data->input = readline(RED "mi" YELLOW "ni" GREEN "sh" CYAN "el" PURPLE "l$ " DEFAULT);
		if (!data->input)
			ft_quit(123, "exit");
		data->input = ft_strtrim(data->input, " \t\n");
		if (data->input[0] == '\0' || is_empty_str(data->input))
			continue ;
		add_history(data->input);
		lexered_params = lexer(data->input);
		parsed_params = parser(lexered_params);
		lstclear(data->lexered_params, &del_content_lexer); //potrebbe dare problemi se albero condivide elementi del lexer
		free(data->lexered_params);
		data->lexered_params = NULL;
		if (!parsed_params)
			continue ;
		set_signals(S_SILENT, true);
		executor(parsed_params);
		treeclear(data->parsed_params, &del_content_parser);
		free(data->parsed_params);
		data->parsed_params = NULL;
	}
}


