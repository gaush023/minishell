/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expasions_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:27 by etakaham          #+#    #+#             */
/*   Updated: 2024/09/09 23:34:51 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*copy_env_value(char *env, t_node *node);

char	*get_env_value(char *var_name, t_mini *mini, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_value;

	env_value = my_strdup("", mini->m_node);
	while (env)
	{
		copy_env_name(env_name, env->value);
		if (ft_strcmp(env_name, var_name) == 0)
		{
			my_free(env_value, mini->m_node);
			env_value = copy_env_value(env->value, mini->m_node);
			return (env_value);
		}
		env = env->next;
	}
	return (env_value);
}

char	*get_var_value(char *arg, int pos, t_mini *mini, t_env *env)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	var_value = NULL;
	if (arg[pos] == '?')
	{
		var_value = my_itoa(mini->ret, mini->m_node);
		return (var_value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
		var_name[i++] = arg[pos++];
	var_name[i] = '\0';
	var_value = get_env_value(var_name, mini, env);
	return (var_value);
}

static int	increment_i(int i, char *arg)
{
	int	count;

	count = 0;
	if (ft_isdigit(arg[i]) == 0)
	{
		if (arg[i] == '\0')
			return (0);
		while (arg[i + 1] && is_env_char(arg[i]) == 1)
		{
			i++;
			count++;
		}
	}
	return (count);
}

int	malloc4expassion(char *arg, t_mini *mini, t_env *env)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, mini, env);
			if (ft_isdigit(arg[i]) == 0)
				i += increment_i(i, arg);
			else
				size--;
		}
		if (arg[i] == '\0')
			break ;
		size++;
	}
	return (size);
}
