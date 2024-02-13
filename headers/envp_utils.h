/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:21:31 by egualand          #+#    #+#             */
/*   Updated: 2024/02/13 17:25:31 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define HASH_TABLE_SIZE 255  //non 256 altrimenti va in loop infinito envp_table_clear
# define REMOVE -1
# define REPLACE 0
# define ADD 1

uint8_t hash(char *str);
void	ft_setenv(char *env_name, char *env_value, bool replace);
char	*ft_getenv(char *env_name);
void	ft_unsetenv(char *env_name);
void    envp_table_init(char **envp);
void	print_envp_table(void);
void	envp_table_clear(t_list **table);

// void    ft_printenv(void); forse serve per il comando env

typedef struct s_envp
{
    char *name; //sarebbe la key
    char *value;
}t_envp;

void    update_env_matrix(t_envp elem, int8_t remove_add_replace);
char	**env_matrix_remove(char **matrix, char *env_name, uint32_t name_len);
char	**env_matrix_replace(char **matrix, t_envp elem, uint32_t name_len, uint32_t value_len);
char	**env_matrix_add(char **matrix, t_envp elem, uint32_t name_len, uint32_t value_len);

#endif