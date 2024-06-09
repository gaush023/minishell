# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 18:00:11 by etakaham          #+#    #+#              #
#    Updated: 2024/06/09 17:10:48 by etakaham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = main_helper.a

SRCS = $(wildcard *.c)

CC = cc
CFLAGS = -Wall -Wextra -Werror

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
