/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:49:32 by sagemura          #+#    #+#             */
/*   Updated: 2024/08/27 19:37:55 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*stop_heredoc(t_token *token, char *line, t_mini *mini)
{
	t_token	*tmp;
	char	*tmp_line;

	tmp_line = my_strdup(line, mini->m_node);
	line = transform_line(line, mini);
	tmp = get_tokens(line, mini);
	if (line == NULL || quote_check(mini, line) == 1)
		return (token);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	token->prev->next = tmp;
	ft_add_history(tmp_line, tmp);
	my_free(line, mini->m_node);
	my_free(tmp_line, mini->m_node);
	return (token);
}

static void	here_doc_write(t_mini *mini, char *line)
{
	ft_putstr_fd(line, mini->heredoc_fd);
	ft_putstr_fd("\n", mini->heredoc_fd);
	my_free(line, mini->m_node);
}

static void	here_doc_end(t_mini *mini)
{
	if (g_sig != SIGNAL_INT)
		mini->heredoc_fd = open("/tmp/heredoc_tmp", O_RDONLY);
	else
		mini->heredoc_fd = open("/dev/null", O_RDONLY);
	if (mini->heredoc_fd == -1)
		return ;
	dup2(mini->heredoc_fd, STDIN);
	ft_close(mini->heredoc_fd);
}

static void	here_doc_loop(t_mini *mini, t_token *token, char *delimiter)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		line = my_readline(" \b", mini->m_node, mini);
		if (g_sig == SIGNAL_INT)
		{
			token = stop_heredoc(token, line, mini);
			mini->ret = 130;
			return ;
		}
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
				return ;
			my_free(line, mini->m_node);
			return ;
		}
		here_doc_write(mini, line);
	}
}

void	here_doc(t_mini *mini, t_token *token)
{
	char	*delimiter;

	g_sig = ON_HERE_DOC;
	delimiter = token->content;
	mini->heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (mini->heredoc_fd == -1)
		return ;
	here_doc_loop(mini, token, delimiter);
	ft_close(mini->heredoc_fd);
	here_doc_end(mini);
}
