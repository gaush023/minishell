#ifndef MINISHELL_H
# define MINISHELL_H

# include "library.h"
# include "struct.h"

# define BUFF_SIZE 4096
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define M_PROMPT "\033[0;36m\033[1m minishell> \033[0m"

# define EMPTY 0
# define CMD 1
# define ARG 2
# define REDIR 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define SEMICOLON 7

# define NOSKIP 0
# define SKIP 1

//main
void	sig_int(int code);
void	sig_quit(int code);
void	ini_sig(void);

//env
int		env_init(t_mini *mini, char **env_ar);
int		secret_env_init(t_mini *mini, char **env_ar);
int		get_shlvl_plus(t_env *env);

//parsing
t_token	*get_tokens(char *line);
void	squish_content(t_mini *mini);
void	parse(t_mini *mini);
void	type_token(t_token *token, int sep);
	//helper_func
void reset_fds(t_mini *mini);
int		ft_panic(char *msg);
int		quotes(char *line, int index);
void	ft_free(void *ptr);
int		is_type(t_token *token, int type);
int		is_types(t_token *token, char *types);
int		check_line(t_mini *mini, t_token *token);

//helper_func/libft
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *s);
char	*ft_itoa(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_putstr_fd(char *s, int fd);

#endif
