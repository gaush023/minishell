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

void	export(char **tokens, t_env *env)
{
	t_env	*new_env;

	if (!ft_equals(tokens[0], "export") || tokens[1] == NULL)
	{
		exit(1);
	}
	new_env = ft_calloc(1, sizeof(t_env));
	ft_memcpy(new_env->value, tokens[1], ft_strlen(tokens[1]));
	new_env->next = NULL;
	while (env->next != NULL)
		env = env->next;
	env->next = new_env;
}
