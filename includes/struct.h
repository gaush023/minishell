#ifndef STRUCT_H
#define STRUCT_H

#include "library.h"

enum e_err{
	ini_set = 1,
	env_set = 2,
	err_token = 3,
	err_pipe = 4,
	err_fork = 5,
};

enum commands{
	co_echo,
	co_cd,
	co_pwd,
	co_export,
	co_unset,
	co_env,
	co_exit,
	co_others,
};

typedef struct s_env
{
	char *value;
	struct s_env *next;
}	 t_env;

typedef struct s_token
{
	char *content;
	int type;
	struct s_token *next;
	struct s_token *prev;
}	 t_token;

typedef struct s_expasion
{
	char *str;
	int i;
	int j;
}	 t_expasion;

typedef struct s_sig
{
	int sigint;
	int sigquit;
	int sig_flag;
	pid_t pid;
}	 t_sig;

extern t_sig g_sig;

typedef struct s_mini
{
	int in;
	int out;
	int flag;
	int ret;
	int fdin;
	int fdout;
	int pipein;
	int pipeout;
	int m_pid;
	int	charge;
	int parent;
	int last;
	int no_exec;
	int exit;
	int heredoc_fd;
	int heredoc_flag;
	t_env *env;
	t_env *secret_env;
	t_token *start;
}	 t_mini;

#endif
