/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:22 by craimond          #+#    #+#             */
/*   Updated: 2024/01/04 19:07:09 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// TODO: fare in modo che le freccette ">>" corrispondano al livello di profondita' della directory della shell
	char *path;

	(void)argc;
	(void)argv;

	path = getenv("PATH");
    // TODO: Fare in modo che execve sia fatto dentro un fork
	execve(get_cmd(path, "clear"), ft_split("clear", ' '), envp);
}