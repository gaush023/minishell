.PHONY: all fclean re clean

NAME		= minishell_lib.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
SRCS		= $(wildcard ./*.c)
OBJS		= $(SRCS:.c=.o)
LIBFT_DIR	= ../libft
LIBFT		= $(LIBFT_DIR)/libft.a

all:$(NAME)

$(NAME):$(OBJS)
	make -C $(LIBFT_DIR)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean:clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re:fclean all
