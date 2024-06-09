/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:56:47 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/09 19:47:28 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

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

int	unset(char **tokens, t_env *env)
{
	if (tokens[1] == NULL)
	{
		return (1);
	}
	if (ft_env_equals(env->value, tokens[1]))
	{
		env = env->next;
		return (1);
	}
	while (env->next->next != NULL)
	{
		if (ft_env_equals(env->next->value, tokens[1]))
		{
			env->next = env->next->next;
			return (1);
		}
		env = env->next;
	}
	return (0);
}
