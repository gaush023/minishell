# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 16:39:35 by sagemura          #+#    #+#              #
#    Updated: 2024/05/01 10:16:30 by sagemura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HELPERFUNC = helperfunc.a
LIBFT = libft.a
PARSING = parsing.a
ENV = env.a
FINISH = finish.a

SRCS = $(wildcard *.c)
LIBFT_DIR = ./helperfunc/libft
HELPERFUNC_DIR = ./helperfunc
PARSING_DIR = ./parsing
ENV_DIR = ./env
FINISH_DIR = ./finish
FT_CMD = ./ft_commands
EXC = ./exec

CC = cc
CFLAGS = -Wall -Wextra -Werror  -g  -I$(LIBFT_DIR) -I$(HELPERFUNC_DIR) -I$(PARSING_DIR) -I$(ENV_DIR) -I$(FINISH_DIR)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(HELPERFUNC_DIR)
	$(MAKE) -C $(PARSING_DIR)
	$(MAKE) -C $(ENV_DIR)
	$(MAKE) -C $(FINISH_DIR)
	$(MAKE) -C $(FT_CMD)
	$(MAKE) -C $(EXC)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(HELPERFUNC_DIR)/$(HELPERFUNC) $(PARSING_DIR)/$(PARSING) $(ENV_DIR)/$(ENV) $(FINISH_DIR)/$(FINISH) $(FT_CMD)/ft_commands.a $(EXC)/exec.a -lreadline

clean:	
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(HELPERFUNC_DIR)
	$(MAKE) clean -C $(PARSING_DIR)
	$(MAKE) clean -C $(ENV_DIR)
	$(MAKE) clean -C $(FINISH_DIR)
	$(MAKE) clean -C $(FT_CMD)
	$(MAKE) clean -C $(EXC)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(HELPERFUNC_DIR)
	$(MAKE) fclean -C $(PARSING_DIR)
	$(MAKE) fclean -C $(ENV_DIR)
	$(MAKE) fclean -C $(FINISH_DIR)
	$(MAKE) fclean -C $(FT_CMD)
	$(MAKE) fclean -C $(EXC)
	rm -f $(NAME)
	
re: fclean all

