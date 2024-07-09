NAME = minishell
SRCS = main.c signal.c env/env.c env/shlvl.c exec/builtin.c exec/cmd_tab.c exec/env_to_array.c exec/error_msg.c exec/exec.c exec/exec_bin.c finish/free_all.c finish/free_token.c finish/ft_panic.c ft_commands/cd.c ft_commands/cd_util.c ft_commands/echo.c ft_commands/env.c ft_commands/export.c ft_commands/pwd.c ft_commands/unset.c ft_commands/update_oldpwd.c helperfunc/free_tab.c helperfunc/ft_equals.c helperfunc/my_readline.c helperfunc/type.c helperfunc/fd.c helperfunc/ft_add_history.c helperfunc/ft_sep.c helperfunc/parsing.c main_helper/ft_here_doc.c main_helper/ft_input.c main_helper/ft_minipipe.c main_helper/ft_redir.c main_helper/minishell.c parsing/expasions_helper.c parsing/get_size4expasions.c parsing/line.c parsing/tokens.c parsing/confirm_tokens.c parsing/ft_copy4expasions.c parsing/get_token_loops_helper.c parsing/make_in_sq_flag.c parsing/transform_line.c parsing/expasions.c parsing/ft_is_env_char.c parsing/get_tokens_helper.c parsing/token_helper.c
LIBFT = libft.a
MALLOC = malloc_lib.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./helperfunc/libft
MALLOC_DIR = ./helperfunc/malloc_lib

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MALLOC_DIR)
	$(CC) $(CFLAGS) $(LIBFT_DIR)/$(LIBFT) $(MALLOC_DIR)/$(MALLOC) $(OBJS) -lreadline -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MALLOC_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(MALLOC_DIR)
	rm -f $(NAME)

re: fclean all
