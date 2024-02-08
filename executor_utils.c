/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:59:44 by craimond          #+#    #+#             */
/*   Updated: 2024/02/08 17:30:09 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char *get_env_name(char *str);

char    *replace_env_vars(char *str)
{
    char        *env_name;
    char        *env_value;
    char        *start;
    char        *tmp;
    uint32_t    len;
    uint32_t    i;

    i = 0;
    while (1)
    {
        start = ft_strdup(&str[i]);
        if (!start)
            ft_quit(ERR_MALLOC, "failed to allocate memory");
        tmp = ft_strchr(start, '$');
        if (!tmp)
            return (free(start), str);
        env_name = get_env_name(tmp + 1);
        env_value = ft_getenv(env_name);
        if (!env_value)
            env_value = "";
        len = ft_strlen(str);
        free(str);
        str = calloc_p(len - ft_strlen(env_name) + ft_strlen(env_value), sizeof(char)); //senza + 1 perche' c'e' gia' il + 1 del carattere $ che non e' considerato nella len
        ft_strlcpy(str, start, tmp - start + 1);
        ft_strcat(str, env_value);
        ft_strcat(str, tmp + 1 + ft_strlen(env_name));
        i += tmp - start;
        free(start);
    }
}

static char *get_env_name(char *str)
{
    char	    *env_name;
    char        *end;

    if (!str || str[0] == '\0' || str[0] == '$' || is_shell_space(str[0]))
        return (NULL);
    env_name = ft_strdup(str);
    if (!env_name)
        ft_quit(ERR_MALLOC, "failed to allocate memory");
    end = ft_strchr(env_name, ' ');
    if (end)
        *end = '\0';
    return (env_name);
}
