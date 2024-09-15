/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/09/16 03:45:50 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_eqaul_env(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '=')
		i++;
	if (s1[i] == '=' && s2[i] == '=')
		return (true);
	return (false);
}

static void	insert_new_env(t_mini *mini, char *tokens)
{
	t_env	*new_env;

	new_env = my_calloc(1, sizeof(t_env), mini->m_node);
	new_env->value = my_calloc(ft_strlen(tokens) + 2, 1, mini->m_node);
	ft_memcpy(new_env->value, tokens, ft_strlen(tokens) + 2);
	while (mini->env->next->next != NULL
		&& !ft_eqaul_env(mini->env->next->value, new_env->value))
		mini->env = mini->env->next;
	if (ft_eqaul_env(mini->env->next->value, new_env->value))
	{
		new_env->next = mini->env->next->next;
		new_env->prev = mini->env;
		mini->env->next->next->prev = new_env;
		mini->env->next = new_env;
		while (mini->env->prev)
			mini->env = mini->env->prev;
		return ;
	}
	mini->env->next->prev = new_env;
	new_env->next = mini->env->next;
	mini->env->next = new_env;
	new_env->prev = mini->env;
	while (mini->env->prev)
		mini->env = mini->env->prev;
}

static void	insert_export_list(t_mini *mini, char *str)
{
	t_env	*new;

	while (mini->export->next)
	{
		if (ft_strcmp(mini->export->value, str) == 0)
		{
			while (mini->export->prev)
				mini->export = mini->export->prev;
			return ;
		}
		mini->export = mini->export->next;
	}
	new = my_calloc(1, sizeof(t_env), mini->m_node);
	new->value = my_strdup(str, mini->m_node);
	new->next = NULL;
	mini->export->next = new;
	new->prev = mini->export;
	while (mini->export->prev)
		mini->export = mini->export->prev;
	sort_env_list(mini->export);
}

static int	export_helper(t_mini *mini, char *tokens, int flag)
{
	size_t	i;

	i = 0;
	insert_export_list(mini, tokens);
	if (!is_env_format(tokens))
	{
		while (tokens[i] != '\0')
		{
			if (tokens[i] == '=')
				break ;
			i++;
		}
		flag = 1;
		return (flag);
	}
	else
		insert_new_env(mini, tokens);
	return (flag);
}

int	export(char **tokens, t_mini *mini)
{
	int	res;
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (tokens[1] == NULL)
		return (print_export_declare(mini));
	if (!ft_equals(tokens[0], "export"))
		return (1);
	while (tokens[i] != NULL)
	{
		res = is_include_equal(tokens[i]);
		if (res == -1)
		{
			write(2, "minishell: export: `", 20);
			write(2, tokens[i], ft_strlen(tokens[i]));
			write(2, "': not a valid identifier\n", 26);
			flag = 1;
		}
		else if (res != 1)
			flag = export_helper(mini, tokens[i], flag);
		i++;
	}
	return (flag);
}
