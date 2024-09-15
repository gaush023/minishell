/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 04:30:42 by sagemura          #+#    #+#             */
/*   Updated: 2024/09/16 04:50:27 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

static int	ft_strisnum(char *str)
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

static size_t	is_max_helper(char *str, size_t i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r')
		i++;
	return (i);
}

static bool	is_max_min(char *str)
{
	unsigned long long	num;
	int					sign;
	size_t				i;

	i = 0;
	sign = 1;
	i = is_max_helper(str, i);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > LLONG_MAX)
			return (true);
		i++;
	}
	if (sign == -1 && num - 1 > LLONG_MAX)
		return (true);
	return (false);
}

void	mini_exit(t_mini *mini, char **cmd, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("exit\n", STDOUT);
		mini->flag = 1;
	}
	if (cmd[1] && cmd[2])
	{
		mini->ret = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		mini->flag = 0;
	}
	else if (cmd[1] && (ft_strisnum(cmd[1]) == 0 || ft_strcmp(cmd[1], "+") == 0
			|| is_max_min(cmd[1])))
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
}
