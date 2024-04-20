/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:26:20 by etakaham          #+#    #+#             */
/*   Updated: 2024/04/20 18:42:35 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	pwd(char **tokens)
{
	char	*work_dir;

	if (!ft_equals(tokens[0], "pwd"))
	{
		exit(0);
	}
	work_dir = ft_calloc(BUF_SIZE, sizeof(char));
	getcwd(work_dir, BUF_SIZE);
	ft_putendl_fd(work_dir, 1);
	free(work_dir);
}
