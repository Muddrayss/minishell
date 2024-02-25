/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:59:44 by craimond          #+#    #+#             */
/*   Updated: 2024/02/25 18:46:35 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char *rebuild_str(char *str, uint32_t i, char *env_value, char *env_name);
static char *get_env_name(char *str, uint32_t *i);
static char *get_env_value(char *env_name);

char    *replace_env_var(char *str, bool to_replace, uint32_t *i)
{
    char    *env_name;
    char    *env_value;
    char    *new_str;

    new_str = str;
    if (to_replace)
    {
        if (str[*i + 1] != '<' && str[*i + 1] != '>')
        {
            env_name = get_env_name(str, i);
            if (!env_name)
                return (str);
            env_value = get_env_value(env_name);
            new_str = rebuild_str(str, *i, env_value, env_name);
            free(str);
        }
    }
    return (new_str);
}

char    *replace_env_vars(char *str)
{
    char        *tmp;
    char        *env_name;
    char        *env_value;
    uint32_t    i;

    i = 0;
    env_name = get_env_name(str, &i);
    while (env_name)
    {
        env_value = get_env_value(env_name);
        tmp = rebuild_str(str, i, env_value, env_name);
        free(str);
        free(env_name);
        free(env_value);
        str = tmp;
        env_name = get_env_name(str, &i);
    }
    return (str);
}

static char *rebuild_str(char *str, uint32_t i, char *env_value, char *env_name)
{
    uint32_t    size;
    char        *new_str;
    uint32_t    env_name_len;

    env_name_len = ft_strlen(env_name);
    size = ft_strlen(str) - env_name_len + ft_strlen(env_value) + 1;
    new_str = (char *)calloc_p(size, sizeof(char));
    ft_strlcpy(new_str, str, i + 1);
    ft_strcat(new_str, env_value);
    ft_strcat(new_str, str + i + env_name_len + 1);
    return (new_str);
}

static char *get_env_name(char *str, uint32_t *i)
{
    char        *end;
    char        *env_name;
    uint32_t    len;

    if (!str)
        return (NULL);
    while (str[*i] && str[*i] != '$')
        (*i)++;
    if (!str[*i] || !str[*i + 1])
        return (NULL);
    if (str[*i + 1] == '$' || is_shell_space(str[*i + 1]))
        (*i)++;
    (*i)++;
    end = ft_strchr(str + *i, ' ');
    if (end)
        len = (uint32_t)(end - (str + *i));
    else
        len = ft_strlen(str + *i);
    env_name = (char *)malloc_p(sizeof(char) * (len + 1));
    ft_strlcpy(env_name, str + *i, len + 1);
    return (env_name);
}

static char *get_env_value(char *env_name)
{
    char *env_value;

    if (env_name[0] == '?')
    {
        env_name[1] = '\0';
        env_value = ft_utoa((uint32_t)g_status); //utoa fa la malloc
    }
    else
        env_value = ft_strdup(ft_getenv(env_name)); //getenv non fa la malloc
    if (!env_value)
        env_value = ft_strdup("");
    if (!env_value)
        ft_quit(ERR_MEM, "Error: failed to allocate memory");
    return (env_value);
}
