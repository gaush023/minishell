/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/08/31 19:43:22 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(char *cmd)
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
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

int	exec_builtin(char **arg, t_mini *mini)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(arg[0], "echo") == 0)
		ret = ft_echo(arg);
	else if (ft_strcmp(arg[0], "cd") == 0)
		ret = ft_cd(arg, mini);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		ret = pwd(arg, mini);
	else if (ft_strcmp(arg[0], "export") == 0)
		ret = export(arg, mini);
	else if (ft_strcmp(arg[0], "unset") == 0)
		ret = unset(arg, mini);
	else if (ft_strcmp(arg[0], "env") == 0)
		ret = env(arg, mini->env);
	else if (ft_strcmp(arg[0], "exit") == 0)
		mini_exit(mini, arg, 0);
	return (ret);
}
