/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:11:21 by sagemura          #+#    #+#             */
/*   Updated: 2024/06/07 17:30:55 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_int(int code)
{
	(void)code;
	rl_on_new_line();
	ft_putstr_fd("\n", STDERR);
	rl_replace_line("", 1);
	if (g_sig == ON_PID || g_sig == ON_HERE_DOC)
	{
		g_sig = SIGNAL_INT;
		if (g_sig == HERE_DOC)
			ft_putstr_fd(M_PROMPT, STDERR);
		else
			ft_putstr_fd("\n", STDERR);
	}
	else
		rl_redisplay();
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig == ON_PID)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putstr_fd(nbr, STDERR);
		ft_putstr_fd("\n", STDERR);
		g_sig = SIGNAL_QUIT;
	}
	else
		ft_putstr_fd("\b\b \b\b", STDERR);
	free(nbr);
}

void	ini_sig(void)
{
	g_sig = SIGNAL_OFF;
}
