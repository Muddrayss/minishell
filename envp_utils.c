/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:23:00 by egualand          #+#    #+#             */
/*   Updated: 2024/02/04 19:17:09 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

uint8_t hash(char *str) //gli va passato il nome con '=' incluso (come getenv("PATH=")) altrimenti non funziona strncmp
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

void	envp_insert(char *env)
{
	uint8_t 	index;
	char		*env_name;
	char		*env_value;
	t_list		*envp;

	envp = get_data()->envp;
	env_name = ft_strdup(str);
	if (!env_name)
		ft_quit(3, "failed to allocate memory");
	env_value = strchr(str, '=') + 1;
	env_name[env_value - str] = '\0'; //preserva l'uguale
	index = hash(env_name);
	free(env_name);
	envp[index] = lstadd_back(&envp[index], lstnew_p(ft_strdup(env_value))); //faccio strdup così posso fare free su lstremoveone in envp_delete
}

char	*envp_get(char *env_name) //gli va passato il nome con '=' incluso (come getenv("PATH=")) altrimenti non funziona strncmp
{
	uint8_t 	index;
	char		*elem;
	t_list		*envp;

	envp = get_data()->envp;
	index = hash(str);
	while (envp[index])
	{
		elem = (char *)envp[index]->content;
		if (ft_strncmp(str, elem, ft_strlen(str) + 1) == 0)
			return (elem->value);
		envp[index] = envp[index]->next;
	}
	return (NULL);
}

void envp_delete(char *env_name) //gli va passato il nome con '=' incluso (come getenv("PATH=")) altrimenti non funziona strncmp
{
	uint8_t 	index;
	char		*elem;
	t_list		*envp;

	envp = get_data()->envp;
	index = hash(env_name);
	while (envp[index])
	{
		elem = (char *)envp[index]->content;
		if (ft_strncmp(env_name, elem, ft_strlen(env_name) + 1) == 0)
		{
			lstremoveone(&envp[index], &free);
			return ;
		}
		envp[index] = envp[index]->next;
	}
}

t_list *envp_init(char **envp)
{
	t_list *new_envp;

	if (!envp)
		return (NULL);
	new_envp = malloc_p(sizeof(t_list) * HASH_SIZE);
	while (*envp)
		envp_insert(*(envp++), new_envp);
	return (new_envp);
}
