/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:31:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/04/16 20:31:21 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static void	non_endl_echo(char **tokens)
{
	return ;
}

void	echo(char **tokens)
{
	if (!ft_equals(tokens[0], "echo"))
	{
		exit(1);
	}
	else if (ft_equals(tokens[1], "-n"))
	{
		non_endl_echo(tokens);
	}
	return ;
}
