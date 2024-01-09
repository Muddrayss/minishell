/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:20 by craimond          #+#    #+#             */
/*   Updated: 2024/01/09 18:08:23 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "libft/libft.h"
# include "parser.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// Errors codes
# define SIGINT_ERROR 20
# define SIGQUIT_ERROR 21

typedef struct s_data
{
	char	*cmd_path;
	char	**cmd_args;
	t_list	**lexered_params_head;
}			t_data;

char		*get_cmd(char *path, char *cmd, t_data *data);
void		free_matrix(char **matrix);
void		ft_quit(int id, char *msg, t_data *data);
// Lexer
t_list		*lexer(char *input, t_data *data);
bool		is_shell_space(char c);
// Signals
void		init_signals(void);
void		del_content(void *content);

#endif
