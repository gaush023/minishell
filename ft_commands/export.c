/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/18 19:24:14 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_node(char *val, t_node *node)
{
	t_env	*new_node;

	new_node = my_calloc(1, sizeof(t_env), node);
	if (new_node == NULL)
		return (NULL);
	new_node->value = ft_strdup(val);
	new_node->next = NULL;
	return (new_node);
}

int	is_include_equal(const char *str)
{
	if (*str == '=')
		return (-1);
	while (*str)
	{
		if (*str == '-' || *str == '+' || ft_isdigit(*str))
			return (-1);
		if (*str == '=')
			break ;
		str++;
	}
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (*str == '=')
			return (0);
		str++;
	}
	return (0);
}

bool	is_env_format(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			return (false);
		if (str[i] == '=')
			break ;
		i++;
	}
	return (true);
}

int	export(char **tokens, t_mini *mini)
{
	t_env	*new_env;
	t_env	*tmp;
	int		res;

	if (!ft_equals(tokens[0], "export") || tokens[1] == NULL)
		return (1);
	res = is_include_equal(tokens[1]);
	if (res == -1)
	{
		write(2, " not a valid identifier", 23);
		return (1);
	}
	else if (res == 1)
		return (0);
	if (!is_env_format(tokens[1]))
		return (1);
	new_env = my_calloc(1, sizeof(t_env), mini->m_node);
	new_env->value = my_calloc(ft_strlen(tokens[1]), 1, mini->m_node);
	ft_memcpy(new_env->value, tokens[1], ft_strlen(tokens[1]));
	while (mini->env->next->next != NULL)
		mini->env = mini->env->next;
	tmp = create_node(mini->env->next->value, mini->m_node);
	new_env->next = tmp;
	mini->env->next = new_env;
	return (0);
}
