/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:26 by craimond          #+#    #+#             */
/*   Updated: 2024/01/27 16:51:27 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define EXEC_FAILURE 1
# define COMMAND_NOT_FOUND 127

void    executor(t_list *parsed_params, t_data *data);
bool    is_heredoc(t_list *redirs);
char    *get_filename(int id1, int id2, t_data *data);
void    fill_heredoc(char *limiter, int fd);

#endif