/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:23:00 by egualand          #+#    #+#             */
/*   Updated: 2024/02/04 20:24:20 by craimond         ###   ########.fr       */
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

//TODO gestire l'overwrite di setenv (hashing non solo con l'env_name?)
void	ft_setenv(char *env_name, char *env_value)
{
	uint8_t 	index;
	t_list		*envp;
	t_envp		*elem;

	envp = get_data()->envp;
	index = hash(env_name);
	elem = malloc_p(sizeof(t_envp));
	elem->name = env_name;
	elem->value = env_value;
	envp[index] = lstadd_back(&envp[index], lstnew_p(elem));
}

char	*ft_getenv(char *env_name)
{
	uint8_t 	index;
	char		*elem;
	t_list		*envp;

	envp = get_data()->envp;
	index = hash(env_name);
	while (envp[index])
	{
		elem = (char *)envp[index]->content;
		if (ft_strcmp(env_name, elem->name) == 0)
			return (elem->value);
		envp[index] = envp[index]->next;
	}
	return (NULL);
}

void	ft_unsetenv(char *env_name)
{
	uint8_t 	index;
	char		*elem;
	t_list		*envp;

	envp = get_data()->envp;
	index = hash(env_name);
	while (envp[index])
	{
		elem = (char *)envp[index]->content;
		if (ft_strcmp(env_name, elem->name) == 0)
		{
			lstremoveone(&envp[index], &free);
			return ;
		}
		envp[index] = envp[index]->next;
	}
}

t_list *envp_init(char **envp)
{
	t_list 		*new_envp;
	char		*env_name;
	char		*env_value;
	uint16_t 	separator_idx;

	if (!envp)
		return (NULL);
	new_envp = malloc_p(sizeof(t_list) * HASH_SIZE);
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
	return (new_envp);
}
