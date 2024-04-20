/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/04/20 18:48:21 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

struct void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (new == NULL || lst == NULL)
		return ;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	export(char **tokens, t_env *env)
{
	t_env	*new_env;

	if (!ft_equals(token[0], "export") || tokens[1] == NULL)
	{
		exit(1);
	}
	new_env = ft_calloc(1, sizeof(t_env));
	ft_memcpy(new_env->value, tokens[1], ft_strlen(tokens[1]));
	new_env->next = NULL;
	ft_lstadd_back(env, new_env);
}
