/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:58:14 by craimond          #+#    #+#             */
/*   Updated: 2024/01/06 13:09:51 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//deve includere solo le librerie che servono a echo, non include minishell.h
//questi file non vanno nel makefile, vengono compilati in runtime con execve (altrimenti ci sarebbero piu' main)

#include "unistd.h"

int main(int argc, char **argv)
{
    printf("%s", argv[1]);
}
