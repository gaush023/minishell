/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/08/27 19:20:49 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static bool	ft_eqaul_env(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '=')
		i++;
	if (s1[i] == '=' && s2[i] == '=')
		return (true);
	return (false);
}

static void	insert_new_env(t_mini *mini, char **tokens)
{
	t_env	*new_env;

	new_env = my_calloc(1, sizeof(t_env), mini->m_node);
	new_env->value = my_calloc(ft_strlen(tokens[1]), 1, mini->m_node);
	ft_memcpy(new_env->value, tokens[1], ft_strlen(tokens[1]));
	while (mini->env->next->next != NULL
		&& !ft_eqaul_env(mini->env->next->value, new_env->value))
		mini->env = mini->env->next;
	if (ft_eqaul_env(mini->env->next->value, new_env->value))
	{
		new_env->next = mini->env->next->next;
		new_env->prev = mini->env;
		mini->env->next->next->prev = new_env;
		mini->env->next = new_env;
		while (mini->env->prev)
			mini->env = mini->env->prev;
		return ;
	}
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
