# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 20:07:51 by sagemura          #+#    #+#              #
#    Updated: 2024/04/20 20:09:41 by sagemura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_commands.a
LIBFT = libft.a

SRCS = $(wildcard *.c)
LIBFT_DIR = ../helperfunc/libft

CC = cc 
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

