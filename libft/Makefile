# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 13:59:13 by egualand          #+#    #+#              #
#    Updated: 2024/01/26 18:30:33 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = ./

SRCS = 	ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
		ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
		ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
		ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memmove.c \
		ft_putnbr_fd.c ft_strdup.c  ft_strlen.c  ft_strrchr.c ft_toupper.c \
		ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c ft_putstr_fd.c \
		ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c ft_strarr_dup.c \
		ft_strarrncpy.c
OBJS = $(SRCS:.c=.o)

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJS = $(BONUS:.c=.o)


CC = cc -g
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = libft.a

all: $(NAME)

$(NAME): $(HEADER) $(OBJS)
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $(SRCS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "Compilation of libft done!"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $(SRCS) $(BONUS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@ranlib $(NAME)
	@echo "Compilation of libft bonus done!"

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "Cleaning of libft done!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Full cleaning of libft done!"

re: fclean all

.PHONY: all bonus clean fclean re
