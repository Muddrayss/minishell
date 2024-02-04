/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:23:00 by egualand          #+#    #+#             */
/*   Updated: 2024/02/04 18:00:51 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

uint8_t hash(char *name)
{
	uint32_t	len;
	uint64_t	hash_value;
	uint32_t	i;

	hash_value = 5381;
	i = 0;
	while (name[i])
	{
		hash_value *= 33;
		hash_value += name[i++];
	}
	return (hash_value % HASH_SIZE);
}

char *envp_search(char *str)
{
	
}

void envp_insert(char *str, t_list *envp)
{
	uint8_t 	index;
	char     	*value_start;
	t_envp		*elem;

	index = hash(str);
	value_start = ft_strchr(str, '=') + 1;
	elem = malloc_p(sizeof(t_envp));
	elem->name = calloc_p(value_start - str + 1);
	ft_strlcpy(elem->name, str, value_start - str + 1);
	elem->value = value_start;
	envp[index] = lstadd_back(&envp[index], lstnew_p(elem));
}

void envp_delete(char *str)
{
	
}

t_list *envp_init(char **envp)
{
	t_list *new_envp;

	if (!envp)
		return (NULL);
	new_envp = malloc_p(sizeof(t_list) * HASH_SIZE);
	while (*envp)
	{
		envp_insert(*envp, new_envp);
		envp++;
	}
	return (new_envp);
}


