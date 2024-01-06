/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:58:14 by craimond          #+#    #+#             */
/*   Updated: 2024/01/06 16:20:14 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//deve includere solo le librerie che servono a echo, non include minishell.h
//questi file non vanno nel makefile, vengono compilati in runtime con execve (altrimenti ci sarebbe confilitto tra main)

#include <unistd.h>
#include <stdbool.h>

static  void    check_flags(bool *is_n, bool *is_e);

int main(int argc, char **argv)
{
    unsigned int i;
    //TODO sostituire con 1 singolo byte per 3 flag con bitwise operators
    bool         is_n;
    bool         is_e;

    check_flags(argv);
    i = 0;
    while (argv[i])
    {
        printf("%s", argv[i++]);
        if (i < argc - 1)
            write(1, ' ', 1);
    }
    if (is_n == false)
        write(1, '\n', 1);
}

//la flag -E forza il setting della flag -e a false

static  void    check_flags(bool *is_n, bool *is_e)
{

} 
