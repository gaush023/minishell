/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/16 17:28:28 by shuga            ###   ########.fr       */
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

int exec_buit(char **arg, t_mini *mini)
{
	int result;

	result = 0;
	if(ft_strcmp(arg[0], "echo") == 0)
		result = ft_echo(arg);
	// other builtins here
	return (result);
	//return value of the builtin
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
		mini->ret = exec_builtin(mini, cmd);
	else if (cmd)
}