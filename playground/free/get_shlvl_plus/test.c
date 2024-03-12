/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:12:49 by sagemura          #+#    #+#             */
/*   Updated: 2024/03/12 15:32:37 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int  env_init(t_mini *mini, char **evn_ar)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return(-1);
	env->value = ft_strdup(evn_ar[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while(evn_ar && evn_ar[i] && evn_ar[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return(-1);
		new->value = ft_strdup(evn_ar[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}


static void	free_env(t_mini *mini)
{
	t_env	*tmp;

	while (mini->env)
	{
		tmp = mini->env->next;
		free(mini->env->value);
        free(mini->env);
		mini->env = tmp;
	}
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}



int	main(int ac, char **av, char **ev)
{
    t_mini mini;
    
    (void)ac;
    (void)av;
    env_init(&mini, ev);
    free_env(&mini);
}
