/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expasions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:24 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/16 00:14:32 by shuga            ###   ########.fr       */
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
	printf("env_value: %s\n", env_value);
  printf("env_value_len: %zu\n", ft_strlen(env_value));
  if (env_value)
		ex->i += var_cpy(ex->str, env_value, ex->i);
	else
		ex->i += 0;
	my_free(env_value, mini->m_node);
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
	ex.str = my_calloc(len + 1, sizeof(char), mini->m_node);
  printf("len: %d\n", len);
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
  printf("expasions: %s\n", ex.str);
  printf("len ex.str: %zu\n", ft_strlen(ex.str));
  printf("%d ex.i\n", ex.i);
  printf("%d ex.j\n", ex.j);
	return (ex.str);
}
