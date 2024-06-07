# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/26 19:51:15 by etakaham          #+#    #+#              #
#    Updated: 2024/06/07 16:00:10 by etakaham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all fclean re clean
NAME	= malloc_lib.a
CC		= CC
CFLAGS	= -Wall -Wextra -Werror
SRCS	= my_calloc.c my_exit.c my_free.c my_malloc.c my_realloc.c malloc_end.c malloc_startup.c
OBJS	= $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME):$(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
