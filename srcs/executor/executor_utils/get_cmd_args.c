/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:31:07 by craimond          #+#    #+#             */
/*   Updated: 2024/03/04 14:48:15 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static uint16_t count_separators(const char *str, const char sep);
static void     quote_split(char *str);

char    **get_cmd_args(char *cmd_str)
{
    char        **cmd_args;
    char        *arg;
    uint16_t    i;

    i = 0;
    quote_split(cmd_str);
    clear_quotes(&cmd_str);
    cmd_args = (char **)malloc_p(sizeof(char *) * (count_separators(cmd_str, '\n') + 2));
    arg = ft_strtok(cmd_str, '\n');
    while (arg)
    {
        cmd_args[i++] = arg;
        arg = ft_strtok(NULL, '\n');
    }
    cmd_args[i] = NULL;
    return (cmd_args);
}

static void    quote_split(char *str)
{
    char    master_quote;

    master_quote = '\0';
    while (*str != '\0')
    {
        if (*str == '\'' || *str == '\"')
        {
            if (master_quote == '\0')
                master_quote = *str;
            else if (master_quote == *str)
                master_quote = '\0';
        }
        if (is_shell_space(*str) && master_quote == '\0')
            *str = '\n';
        str++;
    }
}

static uint16_t   count_separators(const char *str, const char sep)
{
    uint16_t    n;

    n = 0;
    while (*str)
    {
        if (*str == sep)
        {
            n++;
            while (*str && *str == sep)
                str++;
        }
        else
            str++;
    }
    return (n);
}