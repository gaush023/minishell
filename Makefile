.PHONY: all fclean re clean

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
INIT		= $(wildcard srcs/init/*.c)
STARTUP		= $(wildcard srcs/startup/*.c)
SIGNAL_HANDLING = $(wildcard srcs/signal_handling/*.c)
PARSE		= $(wildcard srcs/parse/*.c)
SRCS		= srcs/main.c $(INIT) $(STARTUP) $(SIGNAL_HANDLING) $(PARSE)
OBJS		= $(SRCS:.c=.o)

RLFLAGS		= -lreadline

SANIFLAG	= -fsanitize=address -g

LIBFT_DIR	= ./lib/libft
LIBFT		= $(LIBFT_DIR)/libft.a

MINI_LIB_DIR	= ./lib/minishell_lib
MINI_LIB		= $(MINI_LIB_DIR)/minishell_lib.a

all:$(NAME)

$(NAME):$(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MINI_LIB_DIR)
	$(CC) $(CFLAGS) $(RLFLAGS) $(LIBFT) $(MINI_LIB) $^ -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINI_LIB_DIR)
	$(RM) $(OBJS)

fclean:clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(MINI_LIB_DIR)
	rm -f $(NAME)

re:fclean all
