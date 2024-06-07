# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 16:39:35 by sagemura          #+#    #+#              #
#    Updated: 2024/06/07 16:13:55 by etakaham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HELPERFUNC = helperfunc.a
LIBFT = libft.a
MALLOC = malloc_lib.a
PARSING = parsing.a
ENV = env.a
FINISH = finish.a
FT_CMD = ft_commands.a
MAIN_HELPER = main_helper.a
EXC = exec.a

SRCS = $(wildcard *.c)
LIBFT_DIR = ./helperfunc/libft
MALLOC_DIR = ./helperfunc/malloc_lib
HELPERFUNC_DIR = ./helperfunc
PARSING_DIR = ./parsing
ENV_DIR = ./env
FINISH_DIR = ./finish
FT_CMD_DIR = ./ft_commands
EXC_DIR = ./exec
MAIN_HELPER_DIR = ./main_helper

CC = cc
CFLAGS = -Wall -Wextra -Werror    -I$(LIBFT_DIR) -I$(HELPERFUNC_DIR) -I$(PARSING_DIR) -I$(ENV_DIR) \
-I$(FINISH_DIR) -I$(FT_CMD_DIR) -I$(EXC_DIR) -I$(MAIN_HELPER_DIR) -I$(MALLOC_DIR)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MALLOC_DIR)
	$(MAKE) -C $(HELPERFUNC_DIR)
	$(MAKE) -C $(PARSING_DIR)
	$(MAKE) -C $(ENV_DIR)
	$(MAKE) -C $(FINISH_DIR)
	$(MAKE) -C $(FT_CMD_DIR)
	$(MAKE) -C $(EXC_DIR)
	$(MAKE) -C $(MAIN_HELPER_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(HELPERFUNC_DIR)/$(HELPERFUNC) \
	$(PARSING_DIR)/$(PARSING) $(ENV_DIR)/$(ENV) $(FINISH_DIR)/$(FINISH) $(MALLOC_DIR)/$(MALLOC) \
	$(FT_CMD_DIR)/$(FT_CMD) $(EXC_DIR)/$(EXC) $(MAIN_HELPER_DIR)/$(MAIN_HELPER) -lreadline

clean:	
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MALLOC_DIR)
	$(MAKE) clean -C $(HELPERFUNC_DIR)
	$(MAKE) clean -C $(PARSING_DIR)
	$(MAKE) clean -C $(ENV_DIR)
	$(MAKE) clean -C $(FINISH_DIR)
	$(MAKE) clean -C $(FT_CMD_DIR)
	$(MAKE) clean -C $(MAIN_HELPER_DIR)
	$(MAKE) clean -C $(EXC_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(MALLOC_DIR)
	$(MAKE) fclean -C $(HELPERFUNC_DIR)
	$(MAKE) fclean -C $(PARSING_DIR)
	$(MAKE) fclean -C $(ENV_DIR)
	$(MAKE) fclean -C $(FINISH_DIR)
	$(MAKE) fclean -C $(FT_CMD_DIR)
	$(MAKE) fclean -C $(EXC_DIR)
	$(MAKE) fclean -C $(MAIN_HELPER_DIR)
	rm -f $(NAME)

re: fclean all
