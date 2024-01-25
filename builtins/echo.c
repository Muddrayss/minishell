/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:58:14 by craimond          #+#    #+#             */
/*   Updated: 2024/01/25 16:44:44 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//questi file non vanno nel makefile, vengono compilati in runtime con execve (altrimenti ci sarebbe confilitto tra main)

#include "builtins.h"

static int      check_flag(char **argv, bool *is_n);

int main(int argc, char **argv)
{
    int     i;
    bool    is_n;

    i = check_flag(argv, &is_n);
    while (argv[i])
    {
        write(1, argv[i], ft_strlen(argv[i]));
        if (i < argc - 1)
            write(1, " ", 1);            
        i++;
    }
    if (is_n == false)
        write(1, "\n", 1);
}

static int  check_flag(char **argv, bool *is_n)
{
    int i;

    *is_n = false;
    i = 1;
    if (argv[1][0] != '-')
        return (1);
    while (ft_strcmp(argv[i], "-n") == 0) //TODO gestire caso -nnnnnnnnnn (TRIM)
    {
        i++;
        *is_n = true;
    }
    return (i);
}
