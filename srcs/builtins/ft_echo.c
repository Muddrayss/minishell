/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:58:14 by craimond          #+#    #+#             */
/*   Updated: 2024/02/20 18:31:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int  skip_flags(char **args, bool *is_n);

//TODO quando viene chiamato con flag, readline si scazza
void ft_echo(char **args)
{
    int     i;
    bool    is_n;

    i = skip_flags(args, &is_n);
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if (!is_n)
        ft_putstr_fd("\n", STDOUT_FILENO);
    g_status = EXIT_SUCCESS;
}

static int  skip_flags(char **args, bool *is_n)
{
    int i;
    int j;

    *is_n = false;
    i = 0;
    if (!args[1])
        return (1);
    if (args[1][0] != '-')
        return (1);
    while (args[++i])
    {
        if (args[i][0] == '-')
        {
            j = 1;
            while (args[i][j] == 'n')
                j++;
            *is_n = true;
        }
        else
            break ;
    }
    return (i);
}
