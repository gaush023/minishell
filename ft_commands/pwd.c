/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:26:20 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/03 20:35:07 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(char **tokens)
{
	char	*work_dir;

	if (!ft_equals(tokens[0], "pwd"))
	{
		exit(0);
	}
	work_dir = malloc(BUF_SIZE * sizeof(char));
	getcwd(work_dir, BUF_SIZE);
	ft_putendl_fd(work_dir, 1);
	free(work_dir);
	return (0);
}
