/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:26:09 by etakaham          #+#    #+#             */
/*   Updated: 2024/09/09 23:38:44 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "library.h"

enum				e_err
{
	ini_set = 1,
	env_set = 2,
	err_token = 3,
	err_pipe = 4,
	err_fork = 5,
};

typedef struct s_env
{
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
	int				qute_flag;
}					t_token;

typedef struct s_expasion
{
	char			*str;
	size_t			i;
	size_t			j;
}					t_expasion;

typedef struct s_mini
{
	int				in;
	int				out;
	int				flag;
	int				ret;
	int				fdin;
	int				fdout;
	int				pipein;
	int				pipeout;
	int				m_pid;
	int				charge;
	int				parent;
	int				last;
	int				no_exec;
	int				is_printable;
	int				exit;
	int				heredoc_fd;
	int				pos;
	t_env			*env;
	t_env			*secret_env;
	t_token			*start;
	t_node			*m_node;
}					t_mini;

typedef struct s_args
{
	char			*l;
	int				*flag;
	t_mini			*mini;
	int				i;
	t_token			*token;
	t_token			*tmp_t;
}					t_args;

#endif
