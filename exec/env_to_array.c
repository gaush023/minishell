/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/06/25 20:31:38 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_array(t_env *env, t_mini *mini)
{
	int		count;
	int		i;
	char	**env_array;

	while (env->prev)
		env = env->prev;
	i = 0;
	count = count_env(env);
	env_array = (char **)my_calloc(count + 1, sizeof(char *), mini->m_node);
	while (env)
	{
		env_array[i] = my_strdup(env->value, mini->m_node);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
