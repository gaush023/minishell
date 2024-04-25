/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:41:34 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/25 16:38:35 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_env(t_env *env, t_env *secret_env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		ft_free(tmp->value);
		ft_free(tmp);
	}
	while (secret_env && secret_env->next)
	{
		tmp = secret_env;
		secret_env = secret_env->next;
		ft_free(tmp->value);
		ft_free(tmp);
	}
}

void	free_all(t_mini *mini, int ret)
{
	(void)ret;
	free_env(mini->env, mini->secret_env);
	clear_history();
}
