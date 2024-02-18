/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:30:38 by craimond          #+#    #+#             */
/*   Updated: 2024/02/18 18:13:35 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

bool	is_builtin(char *cmd);
void    exec_builtin(char **cmd_args);
void	ft_echo(char **argv);
void 	ft_cd(char **args);
void	ft_env(char **args);
void	ft_exit(char **args);
void	ft_export(char **args);
void	ft_pwd(char **args);
void	ft_unset(char **args);

#endif