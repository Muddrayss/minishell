/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:58:14 by craimond          #+#    #+#             */
/*   Updated: 2024/02/18 18:38:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int  check_flag(char **argv, bool *is_n);

//TODO fix flag non funziona
void ft_echo(char **argv)
{
    int     i;
    bool    is_n;

    i = check_flag(argv, &is_n);
    while (argv[i])
    {
        ft_putstr_fd(argv[i], STDOUT_FILENO);
        if (argv[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if (!is_n)
        ft_putstr_fd("\n", STDOUT_FILENO);
    g_status = EXIT_SUCCESS;
}

static int  check_flag(char **argv, bool *is_n)
{
    int i;
    int j;

    *is_n = false;
    i = 0;
    if (argv[1][0] != '-')
        return (1);
    while (argv[++i])
    {
        if (argv[i][0] == '-')
        {
            j = 0;
            while (argv[i][j] == 'n')
                j++;
            if (argv[i][j] != '\0')
                return (i);
            *is_n = true;
        }
    }
    return (i);
}
