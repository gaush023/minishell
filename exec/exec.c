/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/19 19:16:23 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < REDIR)
	{
		token = token->next;
		i++;
	}
	if (!(tab = (char **)malloc(sizeof(char *) * i)))
		return (NULL);
	token = start->next;
	tab[0] = start->content;
	i = 1;
	while (token && token->type < REDIR)
	{
		tab[i] = token->content;
		token = token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	mini_exit(t_mini *mini, char **cmd)
{
	mini->exit = 1;
	ft_putstr_fd("exit", STDERR);
	if (cmd[1])
		ft_putstr_fd("☻\n", STDERR);
	else
		ft_putstr_fd("☹︎\n", STDERR);
	if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
}

bool	is_built(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	return (false);
}

int exec_builtin(char **arg, t_mini *mini)
{
	int result;

	result = 0;
	if(ft_strcmp(arg[0], "echo") == 0)
		result = ft_echo(arg);
	// other builtins here
	return (result);
	//return value of the builtin
}

int count_env(t_env *env)
{
	int count;

	count = 0;
	while(env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char **env_to_array(t_env *env)
{
	int count;
	int i;
	char **env_array;

	i = 0;
	count = count_env(env);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	while (env)
	{
		env_array[i] = ft_strdup(env->value);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}


int magic_box(char *path, char *args, t_env *env, t_mini *mini)
{
	char **env_array;
	int ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if(g_sig.pid == 0)
	{
		env_array = env_to_array(env);
		
	}
}

int exec_bin(char **args, t_env *env, t_mini *mini)
{
	int i;
	char **bin;
	char *path;
	int ret;

	i = 0;
	ret = UK_CMD;
	while(env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if(!env || !env->next)
		return (magic_box(args[0], args, env, mini));
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char *cmd;
	int i;

	if (mini->charge == 0)
		return ;
	cmd = cmd_tab(token);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expasions(cmd[i], mini->env, mini->ret);
		i++;
	}
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		mini_exit(mini, cmd);
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = 	exec_builtin(mini, cmd);
	else if (cmd)
		mini->ret = exec_bin(cmd, mini->env, mini);
	
}