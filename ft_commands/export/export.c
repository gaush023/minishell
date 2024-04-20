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
	if (!ft_equals(token[0], "export") || tokens[1] == NULL)
	{
		exit(1);
	}
}
