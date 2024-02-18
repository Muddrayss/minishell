/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:30:38 by craimond          #+#    #+#             */
/*   Updated: 2024/02/18 14:58:53 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

bool	is_builtin(char *cmd);
void	exec_builtin(char **args);
void	ft_cd(char **args);
void	ft_env(char **args);
void	ft_exit(char **args);
void	ft_export(char **args);
void	ft_pwd(char **args);
void	ft_unset(char **args);

#endif