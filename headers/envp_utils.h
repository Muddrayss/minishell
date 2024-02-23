/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:21:31 by egualand          #+#    #+#             */
/*   Updated: 2024/02/23 14:49:54 by craimond         ###   ########.fr       */
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
void	envp_table_clear(t_list **table);
void	envp_matrix_print_env(void);
void    envp_matrix_print_export(void);
void    del_content_envptable(void *content);

typedef struct s_envp
{
    char *name; //sarebbe la key
    char *value;
}t_envp;

void    update_envp_matrix(t_envp elem, int8_t operation);
void	envp_matrix_add(char **matrix, t_envp elem, uint32_t name_len, uint32_t value_len);
void	envp_matrix_remove(char **matrix, char *env_name, uint32_t name_len);
void	envp_matrix_replace(char **matrix, t_envp elem, uint32_t name_len, uint32_t value_len);

#endif