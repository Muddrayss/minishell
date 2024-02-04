/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:59:44 by craimond          #+#    #+#             */
/*   Updated: 2024/02/04 18:44:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char *get_env_name(char *str);

void    replace_env_vars(char **str)
{
    char				*env_name;
    int                 env_name_len;
    char				*env_value;
    unsigned int		i;

    i = 0;
    while ((*str)[i] != '\0')
    {
        if ((*str)[i] == '$')
        {
            env_name = get_env_name(*str + i + 1); //fino a spazio, '\0' o '$'
            if (env_name)
            {
                if (ft_strncmp(env_name, "?", 2) != 0)
                    env_value = ft_getenv(env_name);
                else
                    env_value = ft_itoa(g_status);
                env_name_len = ft_strlen(env_name);
                *str = ft_insert_str(*str, env_value, i, i + env_name_len + 1);
                if (!*str)
                    ft_quit(3, "failed to allocate memory");
                free(env_name);
                i += env_name_len;
            }
        }
        i++;
    }
}

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
            ft_quit(3, "failed to allocate memory");
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
