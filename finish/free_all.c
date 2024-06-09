/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:41:34 by sagemura          #+#    #+#             */
/*   Updated: 2024/05/01 16:18:55 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_env(t_env **env, t_node *node)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		my_free(tmp->value, node);
		my_free(tmp, node);
	}
}

void	free_all(t_mini *mini, int ret)
{
	(void)ret;
	free_env(&(mini->env), mini->m_node);
	free_env(&(mini->secret_env), mini->m_node);
	clear_history();
}
