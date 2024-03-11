# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 16:59:24 by sagemura          #+#    #+#              #
#    Updated: 2024/03/07 20:01:45 by sagemura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = helperfunc.a
LIBFT = libft.a

LIBFT_DIR = ./libft
SRCS = $(wildcard *.c)

CC = CC
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)

OBJS = $(SRCS:.c=.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


