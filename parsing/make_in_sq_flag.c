/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_in_sq_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:36 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/09 23:04:12 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	increment_case_singlequote(int i, char *line, int *str_flag)
{
	str_flag[i] = -2;
	i++;
	while (1)
	{
		if (line[i] == '\'' && line[i - 1] != '\\')
			break ;
		str_flag[i] = 0;
		i++;
	}
	str_flag[i] = -2;
	return (i);
}

int	increment_case_dublequote(int i, char *line, int *str_flag)
{
	str_flag[i] = -2;
	i++;
	while (1)
	{
		if (line[i] == '\"' && line[i - 1] != '\\')
			break ;
		str_flag[i] = 0;
		i++;
	}
	str_flag[i] = -2;
	return (i);
}

int	increment_case_quotetaions(int i, char *line, int *str_flag)
{
	if (line[i] == '\'')
		i = increment_case_singlequote(i, line, str_flag);
	if (line[i] == '\"')
		i = increment_case_dublequote(i, line, str_flag);
	return (i);
}

int	*make_in_sq_flag(char *line, t_mini *mini)
{
	int				*str_flag;
	unsigned int	i;
	int				flag;

	i = 0;
	flag = 0;
	str_flag = my_calloc(ft_strlen(line) + 1, sizeof(int), mini->m_node);
	str_flag[ft_strlen(line)] = -3;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			flag = 1;
			i = increment_case_quotetaions(i, line, str_flag);
		}
		if (line[i] == ' ')
			str_flag[i] = -1;
		else if (flag == 1)
			str_flag[i] = -2;
		else
			str_flag[i] = 0;
		flag = 0;
		i++;
	}
	return (str_flag);
}
