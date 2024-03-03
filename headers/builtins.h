/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:30:38 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 15:38:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

bool is_builtin(const char *const cmd);
void exec_builtin(const char *const *args);

void ft_cd(const char *const *args);
void ft_echo(const char *const *args);
void ft_env(const char *const *args);
void ft_exit(const char *const *args);
void ft_export(const char *const *args);
void ft_pwd(const char *const *args);
void ft_unset(const char *const*args);

#endif