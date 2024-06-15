/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:38:44 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/16 00:20:11 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(char **tokens, t_env *env)
{
	(void)tokens;
	while (env != NULL)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	return (0);
}
