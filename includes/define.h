/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:27:15 by sagemura          #+#    #+#             */
/*   Updated: 2024/06/16 01:08:15 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define BUFF_SIZE 4096

// file descriptor
# define STDIN 0
# define STDOUT 1
# define STDERR 2

// signal
extern int  count;
extern int	g_sig;
# define ON_PID -1
# define ON_HERE_DOC -2
# define SIGNAL_OFF -3
# define SIGNAL_ON -4
# define SIGNAL_INT 130
# define SIGNAL_QUIT 131

// string
# define SYNTAX_ERR " minishell: syntax error near unexpected token `"

// token type
# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7
# define HERE_DOC 8

# define NOSKIP 0
# define SKIP 1

# define M_PROMPT "$> "

# define BUF_SIZE 1024

# define ERR 1
# define EXPANSION -36
# define SUCCESS 0
# define IS_DIR 126
# define UK_CMD 127

# define PATH_MAX 409
# define ERR 1
# define SUCCESS 0

#endif
