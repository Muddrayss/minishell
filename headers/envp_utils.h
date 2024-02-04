/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:21:31 by egualand          #+#    #+#             */
/*   Updated: 2024/02/04 20:15:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define HASH_TABLE_SIZE 256 //e' il numero primo minore piu; vicino a 256

uint8_t hash(char *str);
void	ft_setenv(char *env_name, char *env_value);
char	*ft_getenv(char *env_name);
void    ft_unsetenv(char *env_name);
t_list  *envp_init(char **envp);

typedef struct s_envp
{
    char *name; //sarebbe la key
    char *value;
}t_envp;

#endif