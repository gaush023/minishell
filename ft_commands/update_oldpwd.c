/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_oldpwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:13:18 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/09 14:58:19 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_name(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(dest) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static bool	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_var[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_var, env->value);
		if (ft_strcmp(env_var, var_name) == 0)
		{
			ft_free(env->value);
			env->value = ft_strdup(args);
			return (ERR);
		}
		env = env->next;
	}
	return (SUCCESS);
}

static int	env_add(char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		return (ERR);
	}
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (is_in_env(env, oldpwd) == SUCCESS)
	{
		env_add(oldpwd, env);
	}
	ft_free(oldpwd);
	return (SUCCESS);
}
