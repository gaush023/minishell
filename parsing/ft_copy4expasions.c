/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy4expasions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:27 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/06 16:29:52 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_env_name(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && i < BUFF_SIZE)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*copy_env_value(t_mini *mini)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(mini->env->value) + 1;
	env_value = malloc(sizeof(char) * size_alloc);
	i = 0;
	while (mini->env->value[i] && mini->env->value[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (mini->env->value[i])
		env_value[j++] = mini->env->value[i++];
	env_value[j] = '\0';
	return (env_value);
}
