/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/27 18:51:17 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_include_equal(const char *str)
{
	if (*str == '=')
		return (-1);
	while (*str)
	{
		if (*str == '-' || *str == '+' || ft_isdigit(*str))
			return (-1);
		if (*str == '=')
			break ;
		str++;
	}
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (*str == '=')
			return (0);
		str++;
	}
	return (0);
}

bool	is_env_format(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			return (false);
		if (str[i] == '=')
			break ;
		i++;
	}
	return (true);
}

static int	print_export_declare(t_mini *mini)
{
	t_env	*tmp;

	tmp = mini->env;
	while (tmp->next)
	{
		if (tmp->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	insert_new_env(t_mini *mini, char **tokens)
{
	t_env	*new_env;

	new_env = my_calloc(1, sizeof(t_env), mini->m_node);
	new_env->value = my_calloc(ft_strlen(tokens[1]), 1, mini->m_node);
	ft_memcpy(new_env->value, tokens[1], ft_strlen(tokens[1]));
	while (mini->env->next->next != NULL)
		mini->env = mini->env->next;
	mini->env->next->prev = new_env;
	new_env->next = mini->env->next;
	mini->env->next = new_env;
	new_env->prev = mini->env;
	while (mini->env->prev)
		mini->env = mini->env->prev;
}

int	export(char **tokens, t_mini *mini)
{
	int	res;

	if (tokens[1] == NULL)
		return (print_export_declare(mini));
	if (!ft_equals(tokens[0], "export"))
		return (1);
	res = is_include_equal(tokens[1]);
	if (res == -1)
	{
		write(2, " not a valid identifier", 23);
		return (1);
	}
	else if (res == 1)
		return (0);
	if (!is_env_format(tokens[1]))
		return (1);
	insert_new_env(mini, tokens);
	return (0);
}
