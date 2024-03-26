/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:41:34 by sagemura          #+#    #+#             */
/*   Updated: 2024/03/17 04:27:43 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_stack(t_mini *mini);
static void	free_env(t_mini *mini);

void	free_all(t_mini *mini, int ret)
{
	if (ret != 2)
		free_stack(mini);
	free_env(mini);
	clear_history();
}

static void	free_stack(t_mini *mini)
{
	t_token	*tmp;

	while (mini->start)
	{
		tmp = mini->start->next;
		free(mini->start->content);
		mini->start = tmp;
	}
}

static void	free_env(t_mini *mini)
{
	t_env *tmp;
	t_env *tmp_s;

	while (mini->env)
	{
		tmp = mini->env->next;
		free(mini->env->value);
		free(mini->env);
		mini->env = tmp;
	}
	while (mini->secret_env)
	{
		tmp_s = mini->secret_env->next;
		free(mini->secret_env->value);
		free(mini->secret_env);
		mini->secret_env = tmp_s;
	}
}