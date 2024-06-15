/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:03:07 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/16 00:27:40 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	go_to_path(int opt, t_mini *mini)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (opt == 0)
	{
		update_oldpwd(mini);
		env_path = get_env_path(mini->env, "HOME=", 5);
	}
	else if (opt == 1)
		env_path = get_env_path(mini->env, "OLDPWD=", 7);
	if (env_path == NULL)
	{
		if (opt == 0)
			ft_putstr_fd("cd: HOME not set\n", STDERR);
		else
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR);
		return (ERR);
	}
	ret = chdir(env_path);
	my_free(env_path, mini->m_node);
	if (ret == -1)
		return (ERR);
	return (SUCCESS);
}

char	*get_env_path(t_env *env, char *var, int len)
{
	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0 && env->value[len] == '=')
		{
			return (ft_strdup(env->value + len + 1));
		}
		env = env->next;
	}
	return (NULL);
}
