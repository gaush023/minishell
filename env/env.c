/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:03:46 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/25 20:25:58 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_init(t_mini *mini, char **env_ar)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!env_ar)
		return (1);
	env = my_calloc(1, sizeof(t_env), mini->m_node);
	env->value = my_strdup(env_ar[0], mini->m_node);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_ar && env_ar[0] && env_ar[i])
	{
		new = my_calloc(1, sizeof(t_env), mini->m_node);
		new->value = my_strdup(env_ar[i], mini->m_node);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	env = mini->env;
	new = NULL;
	while (true)
	{
		new = env;
		env = env->next;
		if (!env)
			break ;
		env->prev = new;
	}
	return (0);
}

int	secret_env_init(t_mini *mini, char **env_ar)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = my_calloc(1, sizeof(t_env), mini->m_node);
	env->value = my_strdup(env_ar[0], mini->m_node);
	env->next = NULL;
	mini->secret_env = env;
	i = 1;
	while (env_ar && env_ar[0] && env_ar[i])
	{
		new = my_calloc(1, sizeof(t_env), mini->m_node);
		new->value = my_strdup(env_ar[i], mini->m_node);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
