/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:56:47 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/16 00:20:38 by shuga            ###   ########.fr       */
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

int	unset(char **tokens, t_env *env)
{
	if (tokens[1] == NULL)
	{
		return (0);
	}
	if (ft_env_equals(env->value, tokens[1]))
	{
		env = env->next;
		return (0);
	}
	while (env->next->next != NULL)
	{
		if (ft_env_equals(env->next->value, tokens[1]))
		{
			env->next = env->next->next;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
