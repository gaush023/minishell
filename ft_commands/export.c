/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/04/23 17:28:30 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
# include <stdio.h>

t_env	*create_node(char *val)
{
	t_env *new_node;

	new_node= ft_calloc(1, sizeof(t_env));
	if (new_node == NULL)
		return NULL;
	new_node->value = ft_strdup(val);
	new_node->next = NULL;
	return new_node;
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

void	export(char **tokens, t_env *env)
{
	t_env	*new_env;
	t_env	*tmp;

	if (!ft_equals(tokens[0], "export") || tokens[1] == NULL)
		return ;
	if (!is_env_format(tokens[1]))
		return ;
	new_env = ft_calloc(1, sizeof(t_env));
	new_env->value = ft_calloc(ft_strlen(tokens[1]), sizeof(char));
	ft_memcpy(new_env->value, tokens[1], ft_strlen(tokens[1]));
	while (env->next->next != NULL)
		env = env->next;

	tmp = create_node(env->next->value);
	new_env->next = tmp;
	env->next = new_env;
}
