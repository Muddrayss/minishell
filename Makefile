# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 17:09:33 by craimond          #+#    #+#              #
#    Updated: 2024/01/13 16:09:26 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES_DIR = .

SRCS = 	minishell.c minishell_utils.c lexer.c signals.c parser.c parser_utils.c parser_redirs.c 

OBJS = $(SRCS:.c=.o)
HEADERS = minishell.h lexer.h parser.h error.h

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = minishell

LIBFT = libft.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)

all: $(NAME)

$(LIBFT_LIB):
	@make bonus -C $(LIBFT_DIR) >/dev/null

$(NAME): $(OBJS) $(LIBFT_LIB) $(HEADERS)
	@$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDES_DIR) -L $(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "Compilation of $(NAME) done!"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR) >/dev/null
	@echo "Cleaning of $(NAME) done!"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR) >/dev/null
	@echo "Full cleaning of $(NAME) done!"

re: fclean all

.PHONY: all clean fclean re
