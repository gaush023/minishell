/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expasions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:24 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/23 21:47:08 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	var_cpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i])
		dst[size++] = src[i++];
	return (i);
}

void	insert_var(t_expasion *ex, char *arg, t_mini *mini, t_env *env)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, mini, env);
	if (env_value)
		ex->i += var_cpy(ex->str, env_value, ex->i);
	else
		ex->i += 0;
	if (arg[ex->j] == '?')
		ex->j++;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++;
	}
}

char	*expasions(char *arg, t_mini *mini, t_env *env)
{
	t_expasion	ex;
	int			len;

	len = malloc4expassion(arg, mini, env);
	ex.str = my_calloc(len * 2 + 1, sizeof(char), mini->m_node);
	if (ex.str == NULL)
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.str[ex.i++] = '$';
			else
				insert_var(&ex, arg, mini, env);
		}
		ex.str[ex.i++] = arg[ex.j++];
	}
	ex.str[ex.i] = '\0';
	return (ex.str);
}
