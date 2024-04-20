/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:29:17 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/20 19:29:21 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
/*
** Function: reset_fds
** -------------------
** ファイルディスクリプタをリセットする
*/
void reset_fds(t_mini *mini)
=======
void	ft_close(int fd)
>>>>>>> main
{
	if (fd > 0)
		close(fd);
}

void	reset_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipein = -1;
	mini->pipeout = -1;
	mini->m_pid = -1;
}

void	close_fds(t_mini *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipein);
	ft_close(mini->pipeout);
}

void	reset_std(t_mini *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}
