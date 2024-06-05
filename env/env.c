/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:03:46 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/05 18:03:46 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_init(t_mini *mini, char **evn_ar)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	env->value = ft_strdup(evn_ar[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (evn_ar && evn_ar[0] && evn_ar[i])
	{
		new = malloc(sizeof(t_env));
		new->value = ft_strdup(evn_ar[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int	secret_env_init(t_mini *mini, char **env_ar)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	env->value = ft_strdup(env_ar[0]);
	env->next = NULL;
	mini->secret_env = env;
	i = 1;
	while (env_ar && env_ar[0] && env_ar[i])
	{
		new = malloc(sizeof(t_env));
		new->value = ft_strdup(env_ar[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
