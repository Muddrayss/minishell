/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:21:31 by egualand          #+#    #+#             */
/*   Updated: 2024/02/05 10:49:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define HASH_TABLE_SIZE 256
# define REMOVE -1
# define REPLACE 0
# define ADD 1

uint8_t hash(char *str);
void	ft_setenv(char *env_name, char *env_value);
char	*ft_getenv(char *env_name);
void    ft_unsetenv(char *env_name);
t_list  *envp_init(char **envp);

void    update_env_matrix(t_envp elem, int8_t remove_add_replace);
char	**env_matrix_remove(char **matrix, char *env_name, uint32_t name_len);
char	**env_matrix_replace(char **matrix, t_envp *elem, uint32_t name_len, uint32_t value_len);
char	**env_matrix_add(char **matrix, t_envp elem, uint32_t name_len, uint32_t value_len);
typedef struct s_envp
{
    char *name; //sarebbe la key
    char *value;
}t_envp;

#endif