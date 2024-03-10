/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:20 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:40:39 by egualand         ###   ########.fr       */
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
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
# include <dirent.h>

typedef const char		t_cc;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}						t_list;

typedef struct s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}						t_tree;

typedef struct s_data
{
	char		**envp_matrix;
	t_tree		*envp_tree;
	char		*starting_dir;
	uint16_t	envp_size;
	pid_t		main_pid;
}						t_data;

typedef struct s_dir
{
	t_cc	*basedir;
	DIR		*dir;
}						t_dir;

bool					is_builtin(t_cc *const cmd);
void					exec_builtin(t_cc **const args);

void					ft_cd(t_cc *const *args);
void					ft_echo(t_cc *const *args);
void					ft_env(t_cc *const *args);
void					ft_exit(t_cc *const *args);
void					ft_export(t_cc *const *args);
void					ft_pwd(t_cc *const *args);
void					ft_unset(t_cc *const*args);

typedef struct s_lexer
{
	char	*cmd_str;
	char	token;
}						t_lexer;

static const char		g_lexer_tokens[7] = {'|', ';', '&', '(', ')'};
static const char		g_parser_tokens[7]
	= {'\0', ';', '|', '&', '|', '(', ')'};
static const uint8_t	g_bad_errnos[] = {
	EFAULT,
	EMFILE,
	ENFILE,
	EIO,
	ENOSPC,
	EPIPE,
	EAGAIN,
	ELOOP
};
extern uint8_t			g_status;
static t_cc				g_shell_spaces[] = " \t\n";

t_list					*lexer(const char *input);

# define END				-1
# define CMD				0
# define SEMICOLON			1
# define OR					2
# define AND				3
# define PIPELINE			4
# define SUBSHELL_START		5
# define SUBSHELL_END		6

# define REDIR_INPUT		0 	// < filename
# define REDIR_HEREDOC		1	// << limiter
# define REDIR_OUTPUT		2 	// > filename
# define REDIR_APPEND		3 	// >> filename

# define BEFORE 0
# define AFTER  1

typedef struct s_command
{
	t_list	*redirs;
	char	*cmd_str;
}	t_cmd;

typedef struct s_parser
{
	t_cmd	*cmd;
	int8_t	type;
}	t_parser;

typedef struct s_redir
{
	char	*filename; // o limiter in caso dell heredoc
	int16_t	heredoc_fileno; //eventuale numero da appendere al nome del heredoc
	int8_t	type;
}	t_redir;

t_tree					*parser(t_list *lexered_params);
int8_t					merge_separators(t_list **const lexered_params);
int8_t					check_syntax(const t_list *const lexered_params);
void					tse(t_cc token);
t_list					*fill_redirs(t_cc *const cmd_str);
char					*clear_redirs(t_cc *cmd_str);
bool					is_empty_cmd(const void *const content);
bool					is_redir(t_cc c);

# define EXEC_FAILURE   1
# define CMD_NOT_FOUND  127

void					executor(const t_tree *const parsed_params);
void					create_heredocs(const t_tree *const tree,
							uint8_t *const status);
char					*get_heredoc_filename(uint16_t id);
void					exec_redirs(const t_list *redirs);
char					*get_cmd_path(t_cc *const path, t_cc *const cmd);
char					**get_cmd_args(char *cmd_str);
void					replace_env_vars(char **const str, const bool ign_qout);
void					replace_wildcards(char **str);
void					exec_simple_cmd(t_cc *const path, char *cmd_str);
void					exec(t_cc *const path, char *cmd_str);

# define S_INTERACTIVE  0
# define S_HEREDOC      1
# define S_COMMAND      2
# define S_SILENT       3

void					set_signals(uint8_t mode, bool is_main);
void					envp_init(t_cc **const envp);
void					ft_setenv(t_cc *const name,
							t_cc *const value, const bool replace);
char					*ft_getenv(t_cc *const name);
void					ft_unsetenv(t_cc *const name);

t_tree					*envp_tree_add(t_tree *const root, t_cc *const str);
t_tree					*envp_tree_remove(t_tree *const root,
							t_cc *const name, const uint16_t name_len);
t_tree					*envp_tree_find(const t_tree *const root,
							t_cc *const name, const uint16_t name_len);
void					envp_print_export(const t_tree *const root);

void					envp_matrix_add(t_cc *str);
void					envp_matrix_remove(t_cc *const env_name,
							const uint16_t name_len);
void					envp_print_env(void);

void					ft_putstr_fd(t_cc *const s, const uint16_t fd);
char					*ft_strtok(char *const str, t_cc sep);
char					*ft_strtrim(t_cc *const s1, t_cc *const set,
							const uint8_t alloc_type);
uint16_t				ft_strlen(t_cc *const s);
char					*ft_strdup(t_cc *const s, const uint8_t alloc_type);
char					*ft_strjoin(t_cc *const s1, t_cc *const s2,
							const uint8_t alloc_type);
char					*ft_strnstr(t_cc *const big, t_cc *const little,
							const uint16_t len);
char					*ft_strcpy(char *const dst, t_cc *const src);
uint16_t				ft_strlcpy(char *const dst,
							t_cc *const src, const uint16_t size);
char					*ft_strcat(char *const dst, t_cc *const src);
int16_t					ft_strcmp(t_cc *const s1, t_cc *const s2);
int16_t					ft_strncmp(t_cc *const s1,
							t_cc *const s2, const uint16_t n);
int16_t					ft_strcmp_lower(t_cc *const s1, t_cc *const s2);
char					*ft_strchr(t_cc *const s, t_cc c);
char					ft_tolower(t_cc c);

void					*ft_calloc(const size_t count, const size_t size);
uint16_t				ft_matrixsize(t_cc **const matrix);
bool					is_digit(t_cc c);
int32_t					ft_atoi(t_cc *str);
char					*ft_itoa(const int32_t n);
void					set_errnos(void);
bool					*get_errnos(void);
bool					is_bad_errno(const int errno_value);
bool					is_quote(t_cc c);
bool					is_shell_space(t_cc c);
bool					is_empty_str(t_cc *str);
bool					is_digit(t_cc c);

t_list					*lstnew(const void *const content,
							const uint8_t alloc_type);
void					lstadd_front(t_list **const lst, t_list *const new);
t_list					*lstlast(const t_list *lst);
void					lstadd_back(t_list **const lst, t_list *const new);
void					lstreverse(t_list **const lst);
void					lstclear(t_list **lst,
							void (*del)(void *));
void					lstremoveone(t_list **const head,
							t_list *const to_remove,
							void (*del)(void *));
void					lstremoveif(t_list **const lst,
							bool (*f)(const void *const),
							void (*del)(void *));

t_tree					*treenew(const void *const content,
							const uint8_t alloc_type);
t_tree					*tb(t_tree *const node, const t_tree *const new);
t_tree					*treefirst(const t_tree *root);
void					treeclear(t_tree **const tree,
							void (*del)(void *const));

void					*malloc_p(const size_t size, const uint8_t alloc_type);
void					*calloc_p(const size_t count,
							const size_t size, const uint8_t alloc_type);
void					free_p(void *ptr);
int32_t					chdir_p(t_cc *const path);
DIR						*opendir_p(t_cc *const name);
struct dirent			*readdir_p(const DIR *const dir);
char					*getcwd_p(t_cc *const buf,
							const size_t size, const uint8_t alloc_type);
uint16_t				dup_p(const uint16_t fd);
void					dup2_p(const uint16_t oldfd, const uint16_t newfd);
uint16_t				open_p(t_cc *const path,
							const int32_t flags, const uint16_t mode);
void					close_p(const int16_t fd);
void					reset_fd(int16_t *const fd);
void					pipe_p(int16_t *const fds);
pid_t					fork_p(void);
void					signal_p(const int32_t signo,
							const __sighandler_t handler);
void					sigaction_p(const int32_t signo,
							const struct sigaction *act,
							struct sigaction *oldact);
void					wait_p(int32_t *const status);
void					waitpid_p(const pid_t pid, int32_t *const status,
							const int32_t options);

# define ERR_MEM        3
# define ERR_FD         4
# define ERR_FORK       5
# define ERR_EXEC       6
# define ERR_ENV        7
# define ERR_SIGSETUP   8
# define ERR_WAIT       9

# define N_ERRNOS       200

# define RED "\001\033[1;31m\002"
# define ORANGE "\001\033[1;33m\002"
# define YELLOW "\001\033[1;33m\002"
# define GREEN "\001\033[1;32m\002"
# define BLUE "\001\033[1;34m\002"
# define CYAN "\001\033[1;36m\002"
# define PURPLE "\001\033[1;35m\002"
# define WHITE "\001\033[1;37m\002"
# define BROWN "\001\033[1;33m\002"
# define BLACK "\001\033[1;30m\002"
# define AQUA "\001\033[1;36m\002"
# define DEFAULT "\001\033[0m\002"

# define MAX_FDS	1024
# define TMP        1
# define PERM       2

t_data					*get_data(void);
void					check_args(const int argc,
							t_cc **const argv, t_cc **const envp);
void					init_data(t_cc **const envp);
void					init_general(void);
void					init_signals(void);
char					*clear_quotes(t_cc *const str);
void					gc_add(const void *const ptr);
void					gc_cleanup(void);
void					panic(const uint8_t id, t_cc *const msg);
void					release_resources(void);

char					*get_patn(t_cc *const str, uint16_t *const i,
							uint16_t *const len);
t_list					*sort_result(t_list *matching_files);
char					*add_cwd(t_cc *patn, t_cc *const cwd);
char					*insert_result(t_cc *const str,
							const t_list *const matching_files,
							const uint16_t idx, const uint16_t patn_len);
char					*get_base_dir(t_cc **const patn, bool *const is_r);
t_tree					*skip_till_semicolon(const t_tree *const node);
void					child(const t_tree *const node,
							const int16_t fds[5], const int8_t prev_type);
void					parent(const t_tree *const node,
							int16_t fds[5], const pid_t pid);
void					wait_for_children(const t_tree *const node);
uint16_t				get_n_pipelines(const t_tree *const node);

uint8_t					check_redir_streak(t_cc *const cmd_str);
uint8_t					check_redir_pair(t_cc *const cmd_str);
uint8_t					check_filename_presence(t_cc *const cmd_str);
int8_t					check_redirs(const t_list *lexered_params);

void					interactive_mode(const int32_t signo);
void					heredoc_mode(const int32_t signo);
void					command_mode(const int32_t signo);

#endif