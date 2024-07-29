/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_in_sq_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:36 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/27 17:04:20 by shuga            ###   ########.fr       */
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

static int	*mark_flag(char *line, int *str_flag, unsigned int pos, int flag)
{
	if (line[pos] == ' ')
		str_flag[pos] = -1;
	else if (flag == 1)
		str_flag[pos] = -2;
	else
		str_flag[pos] = 0;
	return (str_flag);
}

int	*make_in_sq_flag(char *line, t_mini *mini)
{
	int				*str_flag;
	unsigned int	pos;
	int				flag;

	pos = 0;
	flag = 0;
	str_flag = my_calloc(ft_strlen(line) + 2, sizeof(int), mini->m_node);
	str_flag[ft_strlen(line)] = -3;
	while (line[pos])
	{
		if (line[pos] == '\'' || line[pos] == '\"')
		{
			flag = 1;
			pos = increment_case_quotetaions(pos, line, str_flag);
		}
		str_flag = mark_flag(line, str_flag, pos, flag);
		flag = 0;
		pos++;
	}
	str_flag[0] = -3;
	return (str_flag);
}
