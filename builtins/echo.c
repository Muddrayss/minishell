/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:58:14 by craimond          #+#    #+#             */
/*   Updated: 2024/01/07 19:39:00 by craimond         ###   ########.fr       */
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
    //gli spazi sono gia gestiti dall' interpretazione automatica di argv
    if (argv[1][0] != '-')
        return (1);
    //libft originale non ha ft_strcmp ma solo ft_strncmp. ft_strncmp non e' sufficiente perche' devo comparare tutta la flag. altrimenti (-nigga) verrebbe interpretata come (-n)
    while (ft_strcmp(argv[i], "-n") == 0)
    {
        i++;
        *is_n = true;
    }
    return (i);
}
