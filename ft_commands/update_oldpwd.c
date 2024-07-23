/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_oldpwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:13:18 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/23 18:18:27 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static bool	is_in_env(t_mini *mini, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_var[BUFF_SIZE];
	t_env	*cpy_env;

	cpy_env = mini->env;
	get_env_name(var_name, args);
	while (cpy_env && cpy_env->next)
	{
		get_env_name(env_var, cpy_env->value);
		if (ft_strcmp(env_var, var_name) == 0)
		{
			my_free(cpy_env->value, mini->m_node);
			cpy_env->value = my_strdup(args, mini->m_node);
			return (ERR);
		}
		cpy_env = cpy_env->next;
	}
	return (SUCCESS);
}

static int	env_add(char *value, t_mini *mini)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*cpy_env;

	cpy_env = mini->env;
	if (cpy_env && cpy_env->value == NULL)
	{
		cpy_env->value = my_strdup(value, mini->m_node);
		return (SUCCESS);
	}
	new = my_calloc(1, sizeof(t_env), mini->m_node);
	new->value = my_strdup(value, mini->m_node);
	while (cpy_env && cpy_env->next && cpy_env->next->next)
		cpy_env = cpy_env->next;
	tmp = cpy_env->next;
	cpy_env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

int	update_oldpwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERR);
	oldpwd = my_strjoin("OLDPWD=", cwd, mini->m_node);
	if (is_in_env(mini, oldpwd) == SUCCESS)
	{
		env_add(oldpwd, mini);
	}
	my_free(oldpwd, mini->m_node);
	return (SUCCESS);
}
