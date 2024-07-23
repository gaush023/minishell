/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:03:07 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/23 19:50:40 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		env_path = get_env_path(mini, "HOME=", 5);
	}
	else if (opt == 1)
		env_path = get_env_path(mini, "OLDPWD=", 7);
	if (env_path == NULL)
		return (go_to_path_helper(opt));
	ret = chdir(env_path);
	my_free(env_path, mini->m_node);
	if (ret == -1)
		return (ERR);
	return (SUCCESS);
}

char	*get_env_path(t_mini *mini, char *var, int len)
{
	t_env	*env;

	printf("Var: %s\n", var);
	printf("len: %d\n", len);
	printf("mini->env->value: %s\n", mini->env->value);
	env = mini->env;
	while (env && env->next != NULL)
	{
		printf("env->value: %s\n", env->value);
		printf("ft_strncmp: %d\n", ft_strncmp(mini->env->value, var, len));
		if (ft_strncmp(env->value, var, len) == 0 && env->value[len] == '=')
		{
			return (my_strdup(env->value + len + 1, mini->m_node));
		}
		env = env->next;
	}
	printf("done\n");
	return (NULL);
}
