#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>

#include "../lib/libft/libft.h"
#include "../lib/minishell_lib/minishell_lib.h"

# define M_PROMPT "\033[0;36m\033[1m $> \033[0m"
# define SUCCESS "\033[0;31m SUCCESS \033[0m"
# define FAILURE "\033[0;31m FAILURE \033[0m"

enum token_types {
	EMPTY,
	END,
	INPUT,
	PIPE,
	REDIR,
	APPEND,
	CMD,
	ARG,
} ;

typedef struct s_token
{
	enum token_types		type;
	char					*com;
	struct s_token			*prev;
	struct s_token			*next;
}							t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	bool	continue_flag;
	int		ret;
	t_env	*env;
	char	*line;
	t_token	*token;
}			t_data;

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	int		sig_flag;
	pid_t	pid;
}			t_sig;

extern t_sig g_sig;

int	get_shlvl_plus(t_env *env);

int	init_env(char **ev, t_env **env_data);
int	init_data(t_data *data);

int		init_sig();
void	sig_start(int code);
void	sig_quit(int code);

int		parse(t_data *data);
int		quotes(char *line, int index);
char	*transform_line(char *line);
int		get_tokens(char *line, t_data *data);

t_sig	g_sig;

#endif
