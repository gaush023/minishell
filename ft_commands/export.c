/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/16 00:20:24 by shuga            ###   ########.fr       */
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

bool	is_env_format(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	export(char **tokens, t_mini *mini)
{
	t_env	*new_env;
	t_env	*tmp;

	if (!ft_equals(tokens[0], "export") || tokens[1] == NULL)
		return (1);
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
