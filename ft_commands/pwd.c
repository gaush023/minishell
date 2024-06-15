/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:26:20 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/16 00:20:28 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(char **tokens, t_mini *mini)
{
	char	*work_dir;

	if (!ft_equals(tokens[0], "pwd"))
		return (1);
	work_dir = my_calloc(BUF_SIZE, sizeof(char), mini->m_node);
	if (!work_dir)
		return (1);
	getcwd(work_dir, BUF_SIZE);
	ft_putendl_fd(work_dir, 1);
	my_free(work_dir, mini->m_node);
	return (0);
}
