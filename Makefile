# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 17:09:33 by craimond          #+#    #+#              #
#    Updated: 2024/02/07 15:45:23 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = minishell.c minishell_utils.c lexer.c parser.c executor.c heredoc.c signals.c envp_matrix.c envp_table.c executor_utils.c protected_methods.c \
		$(addprefix utils/, \
			$(addprefix lst/, lstadd_front.c lstclear.c lstreverse.c lstnew_p.c lstremoveone.c lstdelone.c) \
		 	$(addprefix str/, ft_putstr_fd.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strcat.c ft_strcpy.c ft_strlcpy.c ft_strnstr.c ft_strncmp.c ft_strcmp.c ft_strchr.c) \
			$(addprefix tree/, tree_size.c treeadd_below.c treeclear.c treenew_p.c) \
			$(addprefix general/, ft_freematrix.c ft_atou.c ft_isdigit.c ft_matrixsize.c ft_itoa.c ft_calloc.c))
		
OBJS = $(SRCS:.c=.o)
HEADERS = $(addprefix headers/, minishell.h lexer.h parser.h executor.h signals.h envp_utils.h utils.h protected_methods.h colors.h)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #TODO remove -g
RM = rm -f

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@mkdir -p tmp
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	@echo "Compilation of $(NAME) done!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r tmp
	@$(RM) $(OBJS)
	@echo "Cleaning of $(NAME) done!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Full cleaning of $(NAME) done!"

leaks: all
	@printf "{\n readline\n Memcheck:Leak\n fun:rl_parse_and_bind\n fun:readline_internal_teardown\n fun:rl_initialize\n fun:readline\n}" > readline.supp
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME) 2> leak_report
	@echo "leak report generated"

re: fclean all

.PHONY: all clean fclean re
