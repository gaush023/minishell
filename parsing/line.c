/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:30 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/29 10:48:41 by shuga            ###   ########.fr       */
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

void	parse(t_mini *mini)
{
	char	*line;
	char	*cmd_line;
	t_token	*token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	line = my_readline(M_PROMPT, mini->m_node, mini);
	if ((line == NULL) && (mini->flag == 1))
		return ;
	if (g_sig != SIGNAL_OFF)
		mini->ret = g_sig;
	if (line == NULL || quote_check(mini, line) == 1)
		return ;
	cmd_line = my_strdup(line, mini->m_node);
	line = transform_line(line, mini);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	token = get_tokens(line, mini);
	ft_add_history(cmd_line, token);
	mini->start = token;
	my_free(line, mini->m_node);
}
