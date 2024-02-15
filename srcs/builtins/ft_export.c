/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:27:44 by egualand          #+#    #+#             */
/*   Updated: 2024/02/13 18:24:35 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//TODO gestire export senza opzioni
void	ft_export(char **args) //TODO gestire 'export VAR=' 
{
	int	i;
	char *sep;
	
	i = 0;
	while (args[++i])
	{
		sep = ft_strchr(args[i], '=');
		*sep = '\0';
		ft_setenv(args[i], sep + 1, true); //sep + 1 va in segfault col comando export VAR=
	}
	exit(EXIT_SUCCESS);
}
