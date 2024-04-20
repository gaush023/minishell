/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:29:01 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/20 20:16:09 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "define.h"
# include "library.h"
# include "struct.h"

// main
void	sig_int(int code);
void	sig_quit(int code);
void	ini_sig(void);

// finish
void	free_all(t_mini *mini, int ret);
void	ft_panic(t_mini *mini, char *str, enum e_err err_type);

// env
int		env_init(t_mini *mini, char **env_ar);
int		secret_env_init(t_mini *mini, char **env_ar);
int		get_shlvl_plus(t_env *env);

// exec
void	exec_cmd(t_mini *mini, t_token *token);
int		exec_bin(char **args, t_env *env, t_mini *mini);
char	**env_to_array(t_env *env);
int		error_msg(char *path);
bool	is_builtin(char *cmd);
int		exec_builtin(char **arg, t_mini *mini);

// parsing
t_token	*get_tokens(char *line, t_mini *mini);
t_token	*prev_sep(t_token *token, int skip);
void	squish_content(t_mini *mini);
void	parse(t_mini *mini);
void	type_token(t_token *token, int sep);
char	*expasions(char *arg, t_env *env, int ret);

// helper_func
void	reset_fds(t_mini *mini);
void	ft_free(void *ptr);
void	close_fds(t_mini *mini);
void	ft_close(int fd);
void	reset_std(t_mini *mini);
int		quotes(char *line, int index);
void	ft_free(void *ptr);
void	free_token(t_token *token);
int		is_type(t_token *token, int type);
int		is_types(t_token *token, char *types);
int		check_line(t_mini *mini, t_token *token);

// helper_func/libft
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
int		ft_isalnum(int c);
int		ft_isdigit(int c);

// ft_commands
void	cd(char **tokens);
void	echo(char **tokens);
void	unset(char **tokens, t_env *env);
void	env(char **tokens, t_env *env);
void	export(char **tokens, t_env *env);
void	pwd(char **tokens);

#endif
