/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/06/04 16:09:54 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**cmd_tab(t_token *start, t_mini *mini);

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	mini_exit(t_mini *mini, char **cmd)
{
	mini->flag = 1;
	ft_putstr_fd("exit", STDERR);
	if (cmd[1])
		ft_putstr_fd("☻\n", STDERR);
	else
		ft_putstr_fd("☹︎\n", STDERR);
	if (cmd[1] && cmd[2])
	{
		mini->ret = 800;
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

int	has_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;

	if (mini->charge == 0)
		return ;
	cmd = cmd_tab(token, mini);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expasions(cmd[i], mini);
		i++;
	}
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		mini_exit(mini, cmd);
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = exec_builtin(cmd, mini);
	else if (cmd)
		mini->ret = exec_bin(cmd, mini->env, mini);
	free_tab(cmd, mini->m_node);
	ft_close(mini->pipein);
	ft_close(mini->pipeout);
	mini->pipein = -1;
	mini->pipeout = -1;
	mini->charge = 0;
}
