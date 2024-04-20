/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:56:47 by etakaham          #+#    #+#             */
/*   Updated: 2024/04/20 18:56:47 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	unset(char **tokens, t_env *env)
{
	if (!ft_equals(tokens[0], "unset") || tokens[1] == NULL)
	{
		exit(1);
	}
}
