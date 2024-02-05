/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:59:44 by craimond          #+#    #+#             */
/*   Updated: 2024/02/05 16:44:41 by craimond         ###   ########.fr       */
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

    while (1)
    {
        start = ft_strdup(&str[i]);
        if (!start)
            ft_quit(ERR_MALLOC, "failed to allocate memory");
        tmp = ft_strchr(start, '$');
        if (!tmp)
            return (free(start), str);
        env_name = get_env_name(tmp);
        env_value = ft_getenv(env_name);
        len = ft_strlen(str);
        free(str);
        str = calloc_p(len - ft_strlen(env_name) + ft_strlen(env_value), sizeof(char)); //senza + 1 perche' c'e' gia' il + 1 del carattere $ che non e' considerato nella len
        ft_strlcpy(str, start, tmp - start + 1);
        ft_strcat(str, env_value);
        ft_strcat(str, tmp + ft_strlen(env_name));
        i += tmp - start;
        free(start);
    }
}

static char *get_env_name(char *str)
{
    char	    *env_name;
    uint8_t     len;

    len = 0;
    if (!str || str[len] == '\0' || str[len] == '$' || is_shell_space(str[len]))
        return (NULL);
    while (str[len] != '\0' && !is_shell_space(str[len]) && str[len] != '$')
        len++;
    env_name = (char *)calloc_p(len + 1, sizeof(char));
    return (ft_strcpy(env_name, str), env_name);
}
