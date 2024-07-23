/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:03:07 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/23 22:27:57 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_oldpwd(t_mini *mini);
char	*get_home(t_mini *mini);

static int	go_to_path_helper(int opt)
{
	if (opt == 0)
		ft_putstr_fd("cd: HOOME not set\n", STDERR);
	else
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR);
	return (ERR);
}

int	go_to_path(int opt, t_mini *mini)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (opt == 0)
	{
		update_oldpwd(mini);
		env_path = get_home(mini);
	}
	else if (opt == 1)
	{
		env_path = get_oldpwd(mini);
	}
	if (env_path == NULL)
		return (go_to_path_helper(opt));
	ret = chdir(env_path);
	my_free(env_path, mini->m_node);
	if (ret == -1)
		return (ERR);
	return (SUCCESS);
}

char	*get_oldpwd(t_mini *mini)
{
	t_env	*env;
	char	*result;

	env = mini->env;
	while (env)
	{
		if (!ft_strncmp(env->value, "OLDPWD=", 7) && env->value[6] == '=')
		{
			result = my_strdup(env->value, mini->m_node);
			return (&result[7]);
		}
		env = env->next;
	}
	return (NULL);
}

char	*get_home(t_mini *mini)
{
	t_env	*env;
	char	*result;

	env = mini->env;
	while (env)
	{
		if (!ft_strncmp(env->value, "HOME=", 5) && env->value[4] == '=')
		{
			result = my_strdup(env->value, mini->m_node);
			return (&result[5]);
		}
		env = env->next;
	}
	return (NULL);
}
