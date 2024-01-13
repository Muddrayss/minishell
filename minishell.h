/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:20 by craimond          #+#    #+#             */
/*   Updated: 2024/01/13 15:05:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# include "libft/libft.h"

typedef struct s_data
{
	char	*cmd_path;
	char	**cmd_args;
	t_list	**lexered_params_head;
}			t_data;

# include "parser.h"
# include "lexer.h"
# include "error.h"

char		*get_cmd(char *path, char *cmd, t_data *data);
void		free_matrix(char **matrix);
void		ft_quit(int id, char *msg, t_data *data);
void		del_content(void *content);
bool		is_shell_space(char c);
void		init_signals(void);

#endif
