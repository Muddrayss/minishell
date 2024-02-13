/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:22:05 by craimond          #+#    #+#             */
/*   Updated: 2024/02/13 18:02:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char   *get_wildcard_str(char *str, uint32_t *idx);

void    replace_wildcards(char *str)
{
    char        *wildcard_str;
    char        *wildcard_result;
    uint32_t    idx;

    while (true)
    {
        wildcard_str = get_wildcard_str(str, &idx);
        if (!wildcard_str)
            break ;
        wildcard_result = parse_wildcard_str(wildcard_str);
        str = replace_wildcard(str, idx, wildcard_result);
    }
    return (str);
}

static char   *parse_wildcard_str(char *wildcard_str)
{
    char    *basedir;

    basedir = get_basedir(wildcard_str);
    ft_strjoin(basedir, parse_wildcard_str(wildcard_str));
    
}

static char *get_base_dir(char *wildcard_str)
{
    char        *basedir;
    char        *end;
    uint32_t    len;
    uint32_t    i;

    end = ft_strrchr(wildcard_str, '/');
    if (!end)
        return (getcwd(NULL, 0));
    len = end - wildcard_str;
    basedir = (char *)malloc_p(sizeof(char) * (len + 2));
    i = -1;
    while (++i < len)
        basedir[i] = wildcard_str[i];
    basedir[i] = '/';
    basedir[i + 1] = '\0';
    return (basedir);
}

static char   *get_wildcard_str(char *str, uint32_t *idx)
{
    char    *full_wildcard;
    char    *end;

    while (*str)
    {
        if (*str == '*')
            break ;
        str++;
    }
    if (!*str)
        return (NULL);
    while (!is_shell_space(*str))
        str--;
    *idx = str;
    full_wildcard = ft_strdup(str);
    if (!full_wildcard)
        ft_quit(ERR_MALLOC, "failed to allocate memory");
    end = ft_strchr(full_wildcard, ' ');
    if (end)
        *end = '\0';
    return (full_wildcard);
}
