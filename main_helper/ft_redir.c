/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:24:01 by sagemura          #+#    #+#             */
/*   Updated: 2024/08/27 19:38:05 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir(t_mini *mini, t_token *token, int type)
{
	ft_close(mini->fdout);
	if (type == TRUNC)
		mini->fdout = open(token->content, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRWXU);
	else
		mini->fdout = open(token->content, O_WRONLY | O_CREAT | O_APPEND,
				S_IRWXU);
	if (mini->fdout == -1)
	{
		if (mini->is_printable == 0)
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(token->content, STDERR);
			ft_putstr_fd(": No such file or directory", STDERR);
			ft_putstr_fd("\n", STDERR);
			mini->is_printable = 1;
		}
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}
