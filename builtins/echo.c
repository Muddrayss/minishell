/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:58:14 by craimond          #+#    #+#             */
/*   Updated: 2024/01/07 01:27:54 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//deve includere solo le librerie che servono a echo, non include minishell.h
//questi file non vanno nel makefile, vengono compilati in runtime con execve (altrimenti ci sarebbe confilitto tra main)

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

static int      check_flag(char **argv, bool *is_n);
static short    ft_strcmp(const char *s1, const char *s2);

int main(int argc, char **argv)
{
    int     i;
    bool    is_n;

    i = check_flag(argv, &is_n);
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (i < argc)
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
    if (argv[i][0] != '-')
        return (i);
    while (ft_strcmp(argv[i++], "-n") == 0)
        *is_n = true;
    return (i);
}

//libft originale non ha ft_strcmp ma solo ft_strncmp. ft_strncmp non e' sufficiente perche' devo comparare tutta la flag. altrimenti (-nigga) verrebbe interpretata come (-n)
static short    ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
