/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:26:58 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 18:43:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static uint16_t     ft_strspn(char *str, char sep);
static char         *ft_strpbrk(char *str, char sep);

char    *ft_strtok(char *const str, const char sep)
{
    char            *token;
    char            *end;
    static char     *current_token = NULL;

    if (str)
        current_token = str;
    else if (!current_token)
        return (NULL);
    current_token += ft_strspn(current_token, sep);
    if (*current_token == '\0')
    {
        current_token = NULL;
        return (NULL);
    }
    end = ft_strpbrk(current_token, sep);
    if (end == NULL)
    {
        token = current_token;
        current_token = NULL;
        return (token);
    }
    *end = '\0';
    token = current_token;
    current_token = end + 1;
    return (token);
}

static uint16_t    ft_strspn(char *str, char sep)
{
    uint16_t    i;

    i = 0;
    while (str[i])
    {
        if (str[i] != sep)
            break ;
        i++;
    }
    return (i);
}

static char    *ft_strpbrk(char *str, char sep)
{
    uint16_t    i;

    i = 0;
    while (str[i])
    {
        if (str[i] == sep)
            return (str + i);
        i++;
    }
    return (NULL);
}

