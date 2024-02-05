/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:37:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/05 10:45:35 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

uint8_t hash(char *str)
{
	uint32_t	len;
	uint64_t	hash_value;
	uint32_t	i;

	hash_value = 5381;
	i = 0;
	while (str[i])
	{
		hash_value *= 33;
		hash_value += str[i++];
	}
	return (hash_value % HASH_SIZE);
}

void	ft_setenv(char *env_name, char *env_value, bool replace)
{
	uint8_t 	index;
	t_list		*table;
	t_envp		*elem;

	table = get_data()->envp_table;
	index = hash(env_name);
	elem = malloc_p(sizeof(t_envp));
	elem->name = env_name;
	elem->value = env_value;
	while (table[index])
	{
		if (ft_strcmp(env_name, table[index]->content->name) == 0 && replace)
		{
			table[index]->content = elem;
			update_env_matrix(elem, REPLACE);
			break ;
		}
		table[index] = table[index]->next;
	}
	if (!table[index])
	{
		table = get_data()->envp_table;
		lstadd_back(&table[index], lstnew_p(elem));
		update_env_matrix(elem, ADD);
	}
}

char	*ft_getenv(char *env_name)
{
	uint8_t 	index;
	char		*elem;
	t_list		*table;

	table = get_data()->envp_table;
	index = hash(env_name);
	while (table[index])
	{
		elem = (char *)table[index]->content;
		if (ft_strcmp(env_name, elem->name) == 0)
			return (elem->value);
		table[index] = table[index]->next;
	}
	return (NULL);
}

void	ft_unsetenv(char *env_name)
{
	uint8_t 	index;
	char		*elem;
	t_list		*table;

	table = get_data()->envp;
	index = hash(env_name);
	while (table[index])
	{
		elem = (char *)table[index]->content;
		if (ft_strcmp(env_name, elem->name) == 0)
		{
			lstremoveone(&table[index], &free);
			update_env_matrix(elem, REMOVE);
			break ;
		}
		table[index] = table[index]->next;
	}
}

t_list *envp_table_init(char **envp) //gli viene passata la envp originale
{
	t_list 		*new_envp_table;
	char		*env_name;
	char		*env_value;
	uint16_t 	separator_idx;

	if (!envp)
		return (NULL);
	new_envp_table = malloc_p(sizeof(t_list) * HASH_SIZE);
	while (*envp)
	{
		//metto un \0 al posto del = per avere il nome e il valore separati (senza fare malloc
		env_value = ft_strchr(*envp, '=') + 1;
		separator_idx = env_value - *envp - 1;
		(*envp)[separator_idx] = '\0';
		env_name = *envp;
		ft_setenv(env_name, env_value);
		envp++;
	}
	return (new_envp_table);
}