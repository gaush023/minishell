/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:18:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/25 20:26:48 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdio.h>

int		g_sig = 0;

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q minishell");
// }

/* void *malloc(size_t size) */
/* { */
/* 	static int i = 0; */

/* 	i += size; */
/* 	if (i > MEMORY_SIZE) */
/* 	{ */
/* 		return (NULL); */
/* 	} */
/* 	void *(*libc_malloc)(size_t)  = (void *(*)(size_t))dlsym(RTLD_NEXT,
			"malloc"); */
/* 	return(libc_malloc(size)); */
/* } */

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
	env_init(&mini, ev);
	secret_env_init(&mini, ev);
	get_shlvl_plus(&mini);
	while (mini.flag == 0)
	{
		ini_sig();
		parse(&mini);
		if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
		free_token(mini.start, mini.flag, mini.m_node);
	}
	malloc_end(mini.m_node);
	return (mini.ret);
	(void)ac;
	(void)av;
}
