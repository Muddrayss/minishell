/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:38:46 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 17:04:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*expand_dollar(char *str, uint16_t *const i, const bool ignore_quotes);
static char	*get_env_name(const char *const str, const bool ignore_quotes);
static char	*get_env_value(const char *const env_name);

void	replace_env_vars(char **const str, const bool ignore_quotes)
{
	uint16_t	i;
	char		master_quote;

	i = 0;
	master_quote = '\0';
	while ((*str)[i])
	{
		if (!master_quote && (is_quote((*str)[i])))
			master_quote = (*str)[i];
		else if (master_quote && (*str)[i] == master_quote)
			master_quote = '\0';
		if ((*str)[i] == '$' && (ignore_quotes || master_quote != '\''))
			*str = expand_dollar(*str, &i, ignore_quotes);
		i++;
	}
}

static char *expand_dollar(char *str, uint16_t *const i, const bool ignore_quotes)
{
	char	*new_str;
	char	*env_name;
	char	*env_value;
	char	*start;

	start = str;
	str += *i + 1;
	env_name = get_env_name(str, ignore_quotes);
	if (!env_name)
		return (start);
	env_value = get_env_value(env_name);
	new_str = (char *)calloc_p(ft_strlen(start) + ft_strlen(env_value) - ft_strlen(env_name), sizeof(char));
	ft_strlcpy(new_str, start, str - start);
	ft_strcat(new_str, env_value);
	ft_strcat(new_str, str + ft_strlen(env_name));
	free(start);
	*i += ft_strlen(env_value) - 1;
	return (free_and_null((void **)&env_name), new_str);
}

static char *get_env_name(const char *const str, const bool ignore_quotes)
{
	char				*env_name;
	uint16_t			len;
	static const char	stop_chars[] = {' ', '\t', '\n', '$', '\'', '\"', ':', '\0'};

	len = 0;
	while (str[len] && ft_strchr(stop_chars, str[len]) == NULL)
		len++;
	if (len == 0 && (!is_quote(str[len]) || ignore_quotes))
		return (NULL);
	env_name = (char *)malloc_p(sizeof(char) * (len + 1));
	ft_strlcpy(env_name, str, len + 1);
	return (env_name);
}

static char	*get_env_value(const char *const env_name)
{
	char	*env_value;
	char	*tmp;

	if (env_name[0] == '?')
		env_value = ft_itoa((uint8_t)g_status);
	else
	{
		tmp = strjoin_p(env_name, "=");
		env_value = ft_getenv(tmp);
		free_and_null((void **)&tmp);
	}
	if (!env_value)
		env_value = "";
	return (env_value);
}
