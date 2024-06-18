/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:03:07 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/18 17:47:45 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	go_to_path_helper(int opt)
{
	if (opt == 0)
		ft_putstr_fd("cd: HOME not set\n", STDERR);
	else
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR);
	return (ERR);
}

int	go_to_path(int opt, t_mini *mini)
{
	int		ret;
	t_env	*cpy_env;
	char	*env_path;

	env_path = NULL;
	cpy_env = mini->env;
	if (opt == 0)
	{
		update_oldpwd(mini);
		env_path = get_env_path(cpy_env, "HOME=", 5);
	}
	else if (opt == 1)
		env_path = get_env_path(cpy_env, "OLDPWD=", 7);
	if (env_path == NULL)
		return (go_to_path_helper(opt));
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
