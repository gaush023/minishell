/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:29:01 by sagemura          #+#    #+#             */
/*   Updated: 2024/06/07 19:44:09 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "define.h"
# include "library.h"
# include "struct.h"

# define BUFF_SIZE 4096
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BUF_SIZE 1024

# define EXPANSION -36

// main
void	sig_int(int code);
void	sig_quit(int code);
void	ini_sig(void);

// finish
void	free_all(t_mini *mini, int ret);
void	free_token(t_token *start, int flag);
void	ft_panic(t_mini *mini, char *str, enum e_err err_type);

// env
int		env_init(t_mini *mini, char **env_ar);
int		secret_env_init(t_mini *mini, char **env_ar);
int		get_shlvl_plus(t_mini *mini);

// exec
void	exec_cmd(t_mini *mini, t_token *token);
int		exec_bin(char **args, t_env *env, t_mini *mini);
char	**env_to_array(t_env *env);
int		error_msg(char *path);
bool	is_builtin(char *cmd);
int		exec_builtin(char **arg, t_mini *mini);

// parsing
t_token	*get_tokens(char *line, t_mini *mini);
char	*transform_line(char *line, t_mini *mini);
t_token	*prev_sep(t_token *token, int skip);
void	squish_content(t_mini *mini);
void	parse(t_mini *mini);
void	type_token(t_token *token, int sep);
char	*expasions(char *arg, t_env *env, int ret);
int		malloc4expassion(char *arg, t_env *env, int ret);
char	*get_var_value(char *arg, int pos, t_env *env, int ret);
int		get_var_len(const char *arg, int pos, t_env *env, int ret);
char	*get_env_value(char *var_name, t_env *env);
char	*copy_env_value(char *env);
int		env_value_len(char *env);
char	*copy_env_name(char *dst, char *src);
int		is_env_char(char c);
int		ret_size(int ret);
t_token	*confirm_tokens(t_token *token);
t_token	*make_token(char *str, t_token *prev_token, int *quote_flag, int pos, t_mini *mini);
int		*make_in_sq_flag(char *line, t_mini *mini);
char	*chek_prepareation(char *line);
t_token	*get_tokens_finish(t_token *token);
t_token	*get_token_loops(char *line, int *str_flag, t_mini *mini);

// helper_func
void	reset_fds(t_mini *mini);
void	close_fds(t_mini *mini);
void	ft_close(int fd);
void	reset_std(t_mini *mini);
int		quotes(char *line, int index);
void	free_tab(char **tab);
int		is_type(t_token *token, int type);
int		is_types(t_token *token, char *types);
int		check_line(t_mini *mini, t_token *token);
t_token	*next_sep(t_token *token, int skip);
t_token	*prev_sep(t_token *token, int skip);
bool	ft_equals(const char *s1, const char *s2);
char	*my_readline(const char *prompt, t_node *node);

// main_helper
void	here_doc(t_mini *mini, t_token *token);
void	input(t_mini *mini, t_token *token);
void	redir(t_mini *mini, t_token *token, int type);
int		minipipe(t_mini *mini);
void	minishell(t_mini *mini);

// ft_commands
int		ft_echo(char **args);
int		ft_cd(char **args, t_env *env);
int		unset(char **tokens, t_env *env);
int		env(char **tokens, t_env *env);
int		export(char **tokens, t_env *env);
int		pwd(char **tokens);

#endif
