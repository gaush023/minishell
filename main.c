/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:18:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/08/27 19:22:49 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdio.h>

int			g_sig = 0;

void	mini_init(t_mini *mini)
{
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	if (!mini->in || !mini->out)
	{
		write(2, "Error\n", 6);
		my_exit(1, mini->m_node);
	}
	mini->flag = 0;
	mini->ret = 0;
	mini->no_exec = 0;
	mini->is_printable = 0;
}

static void	main_env(t_mini *mini, char **ev)
{
	env_init(mini, ev);
	secret_env_init(mini, ev);
	get_shlvl_plus(mini);
}

int	main(int ac, char **av, char **ev)
{
	t_mini	mini;

	mini_init(&mini);
	mini.m_node = malloc(sizeof(t_node));
	if (!mini.m_node)
	{
		write(1, "ERROR:insufficient memory\n", 26);
		return (1);
	}
	malloc_startup(mini.m_node);
	main_env(&mini, ev);
	while (mini.flag == 0)
	{
		ini_sig();
		parse(&mini);
		if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
		free_token(mini.start, mini.flag, mini.m_node);
		mini.is_printable = 0;
	}
	malloc_end(mini.m_node);
	return (mini.ret);
	(void)ac;
	(void)av;
}
