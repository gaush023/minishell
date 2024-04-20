/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:12:49 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/19 20:18:54 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s)
{
	char *new;
	size_t len;
	size_t i;

	len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	int		count;
	int		i;
	char	**env_array;

	i = 0;
	count = count_env(env);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	while (env)
	{
		env_array[i] = ft_strdup(env->value);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	env_init(t_mini *mini, char **evn_ar)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (-1);
	env->value = ft_strdup(evn_ar[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (evn_ar && evn_ar[i] && evn_ar[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (-1);
		new->value = ft_strdup(evn_ar[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

// static void	free_env(t_mini *mini)
// {
// 	t_env	*tmp;

// 	while (mini->env)
// 	{
// 		tmp = mini->env->next;
// 		free(mini->env->value);
// 		free(mini->env);
// 		mini->env = tmp;
// 	}
// }

void print_array(char **array)
{
	int i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void free_array(char **array)
{
	int i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

int	main(int ac, char **av, char **ev)
{
	t_mini	mini;
	char	**env_array;
	char	*args[] = {"/bin/ls", NULL};

	(void)ac;
	(void)av;
	env_init(&mini, ev);
	env_array = env_to_array(mini.env);
	(void)args;
	execve("/bin/ls", args, env_array);
	return (0);
}


