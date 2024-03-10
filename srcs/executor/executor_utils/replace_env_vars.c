/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:38:46 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 15:20:01 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*expand_dollar(char *str, uint16_t *const i, const bool ign_quot);
static char	*get_env_name(t_cc *const str, const bool ign_qout);
static char	*get_env_value(t_cc *const env_name);

void	replace_env_vars(char **const str, const bool ign_qout)
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
		if ((*str)[i] == '$' && (ign_qout || master_quote != '\''))
			*str = expand_dollar(*str, &i, ign_qout);
		i++;
	}
}

static char	*expand_dollar(char *str, uint16_t *const i, const bool ign_qout)
{
	char	*new_str;
	char	*env_name;
	char	*env_value;
	char	*start;

	start = str;
	str += *i + 1;
	env_name = get_env_name(str, ign_qout);
	if (!env_name)
		return (start);
	env_value = get_env_value(env_name);
	new_str
		= (char *)calloc_p(ft_strlen(start) + ft_strlen(env_value)
			- ft_strlen(env_name), sizeof(char), TMP);
	ft_strlcpy(new_str, start, str - start);
	ft_strcat(new_str, env_value);
	ft_strcat(new_str, str + ft_strlen(env_name));
	*i += ft_strlen(env_value) - 1;
	return (new_str);
}

static char	*get_env_name(t_cc *const str, const bool ign_qout)
{
	char				*env_name;
	uint16_t			len;
	static const char	stop_chars[]
		= {' ', '\t', '\n', '$', '\'', '\"', ':', '\0'};

	len = 0;
	while (str[len] && ft_strchr(stop_chars, str[len]) == NULL)
		len++;
	if (len == 0 && (!is_quote(str[len]) || ign_qout))
		return (NULL);
	env_name = (char *)malloc_p(sizeof(char) * (len + 1), TMP);
	ft_strlcpy(env_name, str, len + 1);
	return (env_name);
}

static char	*get_env_value(t_cc *const env_name)
{
	char	*env_value;

	if (env_name[0] == '?')
		env_value = ft_itoa((uint8_t)g_status);
	else
		env_value = ft_getenv(ft_strjoin(env_name, "=", TMP));
	if (!env_value)
		env_value = "";
	return (env_value);
}
