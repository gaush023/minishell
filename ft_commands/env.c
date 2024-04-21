/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:38:44 by etakaham          #+#    #+#             */
/*   Updated: 2024/04/20 18:42:41 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	env(char **tokens, t_env *env)
{
	(void)tokens;
	while (env != NULL)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
}
