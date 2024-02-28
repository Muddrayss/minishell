/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:38:46 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 12:56:53 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char *expand_dollar(char *str, uint32_t *i);

char    *replace_env_vars(char *str) //TODO flag per heredoc perche' non deve guardare le quotes
{
    char        master_quote;
    uint32_t    i;

    i = 0;
    master_quote = '\0';
    while (str[i])
    {
        if (!master_quote && (is_quote(str[i])))
            master_quote = str[i];
        else if (master_quote && str[i] == master_quote)
            master_quote = '\0';
        if (master_quote != '\'' && str[i] == '$')
            str = expand_dollar(str, &i);
        i++;
    }
    return (str);
}

static char *expand_dollar(char *str, uint32_t *i)
{
    char        *new_str;
    char        *env_value;
    char        *env_name;
    int32_t     env_name_len;

    str += *i + 1;
    env_name_len = -1;
    while (str[++env_name_len])
        if (str[env_name_len] == ' ' || is_quote(str[env_name_len]) || str[env_name_len] == '$')
            break ;
    env_name = (char *)malloc_p(sizeof(char) * (env_name_len + 1));
    ft_strlcpy(env_name, str, env_name_len + 1);
    if (env_name[0] == '?')
    {
        env_value = ft_utoa((int8_t)g_status);
        env_name_len = 1;
    }
    else
        env_value = ft_getenv(env_name);
    if (!env_value)
        env_value = (char *)calloc_p(1, sizeof(char));
    new_str = (char *)calloc_p(*i + ft_strlen(str) + ft_strlen(env_value) - ft_strlen(env_name) + 1, sizeof(char));
    ft_strlcpy(new_str, str - *i - 1, *i + 1);
    ft_strcat(new_str, env_value);
    ft_strcat(new_str, str + env_name_len);
    *i += ft_strlen(env_value) - 1;
    return (free(env_value), free(env_name), new_str);
}