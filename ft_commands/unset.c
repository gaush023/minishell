/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:56:47 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/25 21:18:07 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_env_equals(char *value, char *token)
{
	size_t	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (value[i] != token[i])
		{
			return (false);
		}
		i++;
	}
	if (value[i] != '=')
		return (false);
	return (true);
}

int	unset(char **tokens, t_mini *mini)
{
	t_env *env;

	env = mini->env;
	if (tokens[1] == NULL)
	{
		return (0);
	}
	while (env->prev)
		env = env->prev;
	while (env->next)
	{
		if (ft_env_equals(env->value, tokens[1]))
		{
			if (env->prev)
				env->prev->next = env->next;
			if (env->next)
				env->next->prev = env->prev;
		}
		env = env->next;
	}
	mini->env = env;
	while (mini->env->prev)
		mini->env = mini->env->prev;
	return (0);
}
