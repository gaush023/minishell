/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:07:12 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/07 19:04:21 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_shlvl_plus(t_mini *mini)
{
	int		shell_lvl;
	char	*tmp;
	char	*str_shelvl;
	t_env	*env;

	env = mini->env;
	while (env && env->next)
	{
		if (ft_strncmp(env->value, "SHLVL=", 5) == 0)
		{
			tmp = ft_strchr(env->value, '=') + 1;
			shell_lvl = ft_atoi(tmp) + 1;
			str_shelvl = my_itoa(shell_lvl, mini->m_node);
			my_free(env->value, mini->m_node);
			env->value = my_strjoin("SHLVL=", str_shelvl, mini->m_node);
			my_free(str_shelvl, mini->m_node);
			return (0);
		}
		env = env->next;
	}
	return (0);
}
