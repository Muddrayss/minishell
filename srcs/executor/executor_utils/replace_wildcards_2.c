/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:59:44 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 15:20:21 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	find_pattern_start(t_cc *const str,
	uint16_t *const i, char *const master_quote)
{
	*master_quote = '\0';
	while (str[*i])
	{
		if (!*master_quote && is_quote(str[*i]))
			*master_quote = str[*i];
		else if (*master_quote && str[*i] == *master_quote)
			*master_quote = '\0';
		if (!*master_quote && str[*i] == '*')
			break ;
		(*i)++;
	}
}

// New function to extract the pattern
static char	*extract_pattern(t_cc *const str, uint16_t *i, uint16_t *const len)
{
	char		*patn;
	const char	stop_chars[]
		= {' ', '\t', '\n', '\"', '\'', '\0'};

	if (str[*i] != '*')
		return (NULL);
	while (*i > 0 && !is_shell_space(str[*i - 1]))
		(*i)--;
	*len = 1;
	while (!ft_strchr(stop_chars, str[*i + *len]))
		(*len)++;
	patn = (char *)malloc_p(sizeof(char) * (*len + 1), TMP);
	ft_strlcpy(patn, &str[*i], *len + 1);
	return (clear_quotes(patn));
}

// Refactored get_patn function using the two new functions
char	*get_patn(t_cc *const str, uint16_t *const i, uint16_t *const len)
{
	char	master_quote;

	if (!str)
		return (NULL);
	find_pattern_start(str, i, &master_quote);
	return (extract_pattern(str, i, len));
}

t_list	*sort_result(t_list *matching_files)
{
	const t_list *const	head = matching_files;
	t_list				*next;
	char				*tmp;

	while (matching_files)
	{
		next = matching_files->next;
		while (next)
		{
			if (ft_strcmp_lower(matching_files->content, next->content) > 0)
			{
				tmp = matching_files->content;
				matching_files->content = next->content;
				next->content = tmp;
			}
			next = next->next;
		}
		matching_files = matching_files->next;
	}
	return ((t_list *)head);
}

char	*get_base_dir(t_cc **const patn, bool *const is_r)
{
	char		*basedir;
	uint16_t	end;
	uint16_t	i;

	end = 0;
	i = 0;
	while ((*patn)[i] && (*patn)[i] != '*')
	{
		if ((*patn)[i] == '/')
			end = i;
		i++;
	}
	basedir = (char *)malloc_p(sizeof(char) * (end + 1), TMP);
	ft_strlcpy(basedir, *patn, end + 1);
	*patn += end + 1;
	if (!basedir[0])
	{
		*is_r = true;
		return (ft_strdup("/", TMP));
	}
	return (basedir);
}
