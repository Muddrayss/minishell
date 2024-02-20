/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:37:08 by craimond          #+#    #+#             */
/*   Updated: 2024/02/20 17:36:11 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

uint8_t hash(char *str)
{
	uint64_t	hash_value;
	uint32_t	i;

	hash_value = 5381;
	i = 0;
	while (str[i])
	{
		hash_value *= 33;
		hash_value += (unsigned char)str[i++];
		hash_value++;
	}
	return (hash_value % HASH_TABLE_SIZE);
}

//a differenza di setenv e getenv originali il nome gli va passato senza '=' perche' viene tagliato da envp_table_init
void	ft_setenv(char *env_name, char *env_value, bool replace)
{
	uint8_t 	index;
	t_list		**table;
    t_list      *bucket;
    t_envp      *elem;
	t_envp		*new_elem;

	table = get_data()->envp_table;
	index = hash(env_name);
	new_elem = malloc_p(sizeof(t_envp));
	new_elem->name = ft_strdup(env_name);
	new_elem->value = ft_strdup(env_value);
	if (!new_elem->name || !new_elem->value)
		ft_quit(ERR_MEM, "Error: failed to allocate memory");
    bucket = table[index];
	while (bucket) //ci entra solo se c'e' una collision
	{
        elem = (t_envp *)bucket->content;
		if (ft_strcmp(env_name, elem->name) == 0) //va bene strcmp perche' compara anche il '\0
		{
			if (replace)
			{
				free(elem->name); //cosi' facendo sto liberando anche il value essendo la stessa stringa
				free(elem->value);
				bucket->content = new_elem;
				update_env_matrix(*new_elem, REPLACE);
			}
			return ;
		}
		bucket = bucket->next;
	}
	if (!bucket) //se non e' presente lo aggiunge
	{
		lstadd_front(&table[index], lstnew_p(new_elem));
		update_env_matrix(*new_elem, ADD);
	}
}

char	*ft_getenv(char *env_name)
{
	uint8_t 	index;
	t_envp		*elem;
	t_list		**table;
    t_list      *bucket;

	table = get_data()->envp_table;
	index = hash(env_name);
    bucket = table[index];
    while (bucket)
	{
		elem = (t_envp *)bucket->content;
		if (ft_strcmp(env_name, elem->name) == 0)
			return (elem->value);
		bucket = bucket->next;
	}
	return (NULL);
}

void	ft_unsetenv(char *env_name)
{
	uint8_t 	index;
	t_envp		*elem;
	t_list		**table;
    t_list      *bucket;

	table = get_data()->envp_table;
	index = hash(env_name);
    bucket = table[index];
	while (bucket)
	{
		elem = (t_envp *)bucket->content;
		if (ft_strcmp(env_name, elem->name) == 0)
		{
			lstremoveone(&table[index], bucket, &free);
			update_env_matrix(*elem, REMOVE);
			break ;
		}
		bucket = bucket->next;
	}
}

void    envp_table_init(char **envp) //gli viene passata la envp originale
{
	char		*env_name;
	char		*env_value;
	uint32_t 	separator_idx;

    //onn c'e' bisogno di contorllare se envp == NULL perche' la prendiamo con getenv_p
	get_data()->envp_table = calloc_p(HASH_TABLE_SIZE, sizeof(t_list *)); //uso calloc cosi' inizializza tutti i bucket a NULL
	while (*envp)
	{
		//metto un \0 al posto del = per avere il nome e il valore separati (senza fare malloc
		env_value = ft_strchr(*envp, '=') + 1;
		separator_idx = (uint32_t)(env_value - *envp - 1);
		(*envp)[separator_idx] = '\0';
		env_name = *envp;
		ft_setenv(env_name, env_value, false); //all'inizio non ci possono essere doppioni quindi metto false
		envp++;
	}
}

void	print_envp_table(bool is_export)
{
	uint8_t		i;
	t_list		*bucket;
	t_envp		*elem;

	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		bucket = get_data()->envp_table[i];
		while (bucket)
		{
			elem = (t_envp *)bucket->content;
			if (elem->value[0] && !is_export)
				printf("%s=%s\n", elem->name, elem->value);
			else if (is_export)
			{
				printf("declare -x %s", elem->name);
				if (elem->value[0])
					printf("\"%s\"", elem->value);
				printf("\n");
			}
			bucket = bucket->next;
		}
		i++;
	}
}

void	envp_table_clear(t_list **table)
{
	uint8_t		i;

	i = 0;
	while (i < HASH_TABLE_SIZE)
		lstclear(&table[i++], &del_content_envptable);
}

void	del_content_envptable(void *content)
{
	t_envp	*elem;

	elem = (t_envp *)content;
	free(elem->name);
	free(elem->value);
	free(elem);
}