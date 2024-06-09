# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 16:39:35 by sagemura          #+#    #+#              #
#    Updated: 2024/06/07 18:05:49 by etakaham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = env.a
HELPERFUNC = helperfunc.a
LIBFT = libft.a

SRCS = $(wildcard *.c)
LIBFT_DIR = ../../libft
MALLOC_DIR = ../../malloc_dir
HELPERFUNC_DIR = ../helperfunc

CC = cc 
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(HELPERFUNC_DIR) -I$(MALLOC_DIR)

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

