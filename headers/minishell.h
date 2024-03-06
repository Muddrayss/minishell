/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:20 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 21:11:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO rendere piu leggibile sta distinzione tra risorse (utils si confondono, lo stack e' una lista, le funzioni standard delle liste non sono piu standard)

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
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
# include <dirent.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_data
{
	char		**envp_matrix;
	t_tree		*envp_tree;
	char		*starting_dir;
	uint16_t	envp_size;
	pid_t		main_pid;
}	t_data;

# include "builtins.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "signals.h"
# include "envp.h"
# include "utils.h"
# include "protected_methods.h"
# include "errors.h"
# include "colors.h"

extern uint8_t		g_status;
static const char	g_shell_spaces[] = " \t\n";

# define MAX_FDS	1024
# define TMP        1
# define PERM       2

t_data *get_data(void);
void	check_args(const int argc, const char **const argv, const char **const envp);
void	init_data(const char **const envp);
void	init_general(void);
char	*clear_quotes(const char *const str);
void	gc_add(const void *const ptr);
void    gc_cleanup();
void	panic(const uint8_t id, const char *const msg);
void	release_resources(void);

#endif