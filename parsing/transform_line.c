/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:30 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/18 20:44:48 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("><|;", line[i]))
		return (0);
	else if (ft_strchr("><|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

static bool	transform_line_loop_helper(char *line, t_mini *mini, int i)
{
	if (line[i] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>' 1\n", 2);
		mini->ret = 2;
		return (FALSE);
	}
	if (line[i] == '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline 2'\n",
			2);
		mini->ret = 2;
		return (FALSE);
	}
	return (TRUE);
}

static char	*allo_new(char *line, t_mini *mini)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	new = my_calloc(i + 2 * count + 1, sizeof(char), mini->m_node);
	if (!new)
		return (NULL);
	return (new);
}

static char	*transform_line_loop(char *line, t_mini *mini, int i, int j)
{
	char	*new;

	new = allo_new(line, mini);
	if (!new)
		return (NULL);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i + 1] != ' ')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i - 1] != '|' && (line[i] == '>' || line[i] == '<'))
				new[j++] = line[i++];
			if (transform_line_loop_helper(line, mini, i) != TRUE)
				return (NULL);
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	return (new);
}

char	*transform_line(char *line, t_mini *mini)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = transform_line_loop(line, mini, i, j);
	my_free(line, mini->m_node);
	return (new);
}
