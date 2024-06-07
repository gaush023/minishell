/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:07:12 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/05 18:07:12 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_shlvl_plus(t_env *env)
{
	int		shell_lvl;
	char	*tmp;
	char	*str_shelvl;

	while (env && env->next)
	{
		if (ft_strncmp(env->value, "SHLVL=", 5) == 0)
		{
			tmp = ft_strchr(env->value, '=') + 1;
			shell_lvl = ft_atoi(tmp) + 1;
			str_shelvl = ft_itoa(shell_lvl);
			free(env->value);
			env->value = ft_strjoin("SHLVL=", str_shelvl);
			free(str_shelvl);
			return (0);
		}
		env = env->next;
	}
	return (0);
}
