# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 17:09:33 by craimond          #+#    #+#              #
#    Updated: 2024/02/20 15:27:55 by egualand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LEXER_SRCS = $(addprefix lexer/, lexer.c)
PARSER_SRCS = $(addprefix parser/, parser.c parser_redirs.c parser_utils.c)
EXECUTOR_SRCS = $(addprefix executor/, executor.c executor_utils.c heredoc.c get_cmd_path.c replace_env_vars.c replace_wildcards.c)
BUILTIN_SRCS = $(addprefix builtins/, builtins_handler.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c)
GENERAL_SRCS = minishell.c minishell_utils.c signals.c envp_matrix.c envp_table.c protected_methods.c xmalloc.c
GENERAL_UTILS_SRCS = $(addprefix general/, ft_freematrix.c ft_atou.c ft_isdigit.c ft_matrixsize.c ft_utoa.c ft_calloc.c)
LST_UTILS_SRCS = $(addprefix lst/, lstadd_front.c lstclear.c lstreverse.c lstnew_p.c lstremoveone.c lstdelone.c lstdelif.c lstsort.c)
STR_UTILS_SRCS = $(addprefix str/, ft_putstr_fd.c ft_split.c ft_strtrim.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strcat.c ft_strcpy.c ft_strlcpy.c ft_strnstr.c ft_strncmp.c ft_strcmp.c ft_strchr.c)
TREE_UTILS_SRCS = $(addprefix tree/, tree_size.c treeadd_below.c treeclear.c treenew_p.c)

UTILS_SRCS = $(addprefix utils/, $(GENERAL_UTILS_SRCS) $(STR_UTILS_SRCS) $(LST_UTILS_SRCS) $(TREE_UTILS_SRCS))
SRCS = $(addprefix srcs/, $(GENERAL_SRCS) $(LEXER_SRCS) $(PARSER_SRCS) $(EXECUTOR_SRCS) $(UTILS_SRCS) $(BUILTIN_SRCS))		
OBJS = $(SRCS:.c=.o)
HEADERS = $(addprefix headers/, minishell.h lexer.h parser.h executor.h signals.h envp_utils.h utils.h protected_methods.h colors.h)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g #TODO remove -g
RM = rm -f

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p tmp
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	@echo "Compilation of $(NAME) done!"

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r tmp
	@$(RM) $(OBJS)
	@echo "Cleaning of $(NAME) done!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Full cleaning of $(NAME) done!"

leaks: all
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME) 2> leak_report
	@echo "leak report generated"

re: fclean all

.PHONY: all clean fclean re
