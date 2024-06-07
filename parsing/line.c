/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:30 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/07 19:49:12 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("><|;", line[i]))
		return (0);
	else if (ft_strchr("><|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
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

char	*transform_line(char *line, t_mini *mini)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = allo_new(line, mini);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && (line[i] == '>' || line[i] == '<'))
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	my_free(line, mini->m_node);
	return (new);
}

int	quote_check(t_mini *mini, char *line)
{
	if (quotes(line, INT_MAX) != 0)
	{
		ft_putstr_fd("quote error\n", STDERR);
		my_free(line, mini->m_node);
		mini->ret = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

void	parse(t_mini *mini)
{
	char	*line;
	t_token	*token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	line = my_readline(M_PROMPT, mini->m_node);
	if ((line == NULL) && (mini->flag == 1))
		return ;
	if (line != NULL)
		add_history(line);
	if (g_sig != SIGNAL_OFF)
		mini->ret = g_sig;
	if (line == NULL || quote_check(mini, line) == 1)
		return ;
	line = transform_line(line, mini);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	token = NULL;
	token = get_tokens(line, mini);
	mini->start = token;
	my_free(line, mini->m_node);
	return ;
}
