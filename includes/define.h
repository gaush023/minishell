/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:27:15 by sagemura          #+#    #+#             */
/*   Updated: 2024/05/07 19:40:41 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define BUFF_SIZE 4096

// file descriptor
# define STDIN 0
# define STDOUT 1
# define STDERR 2

// prompt
# define M_PROMPT "\033[0;36m\033[1m $> \033[0m"
# define M_SUCCESS "\033[0;31mSUCCESS\033[0m"
# define M_FAILURE "\033[0;31mFAILURE\033[0m"


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

# define BUF_SIZE 1024

# define ERR 1
# define EXPANSION -36
# define SUCCESS 0
# define IS_DIR 126
# define UK_CMD 127

#endif
