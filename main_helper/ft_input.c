/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:23:18 by sagemura          #+#    #+#             */
/*   Updated: 2024/06/03 20:23:27 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input(t_mini *mini, t_token *token)
{
	ft_close(mini->fdin);
	mini->fdin = open(token->content, O_RDONLY, S_IRUSR);
	if (mini->fdin < 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->content, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->ret = 200;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}