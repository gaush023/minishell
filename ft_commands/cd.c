/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:21:07 by etakaham          #+#    #+#             */
/*   Updated: 2024/04/20 18:42:39 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	cd(char **tokens)
{
	char	*work_dir;
	char	*new_work_dir;

	if (!ft_equals(tokens[0], "cd") || tokens[1] == NULL)
	{
		exit(1);
	}
	work_dir = ft_calloc(BUF_SIZE, sizeof(char));
	getcwd(work_dir, BUF_SIZE);
	new_work_dir = ft_strjoin(work_dir, tokens[1]);
	chdir(new_work_dir);
	free(work_dir);
	free(new_work_dir);
	return ;
}
