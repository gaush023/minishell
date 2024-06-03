/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:49:32 by sagemura          #+#    #+#             */
/*   Updated: 2024/06/03 20:21:10 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*stop_heredoc(t_token *token, char *line)
{
	t_token	*tmp;

	line = transform_line(line);
	tmp = get_tokens(line);
	token->prev->next = tmp;
	return (token);
}

static void	here_doc_write(t_mini *mini, char *line)
{
	ft_putstr_fd(line, mini->heredoc_fd);
	ft_putstr_fd("\n", mini->heredoc_fd);
	ft_free(line);
}

static void	here_doc_end(t_mini *mini)
{
	if (g_sig.sigint != 1)
		mini->heredoc_fd = open("/tmp/heredoc_tmp", O_RDONLY);
	else
		mini->heredoc_fd = open("/dev/null", O_RDONLY);
	if (mini->heredoc_fd == -1)
		return ;
	dup2(mini->heredoc_fd, STDIN);
	ft_close(mini->heredoc_fd);
	if (g_sig.sigint != 1)
		g_sig.heredoc_flag = 0;
}

static int	here_doc_loop(t_mini *mini, t_token *token, char *delimiter)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = readline(" \b");
		if (g_sig.sigint == 1)
		{
			token = stop_heredoc(token, line);
			return (0);
		}
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
			{
				ft_putstr_fd("\n", 1);
				ft_close(mini->heredoc_fd);
				return (1);
			}
			ft_free(line);
			return (0);
		}
		here_doc_write(mini, line);
	}
}

void	here_doc(t_mini *mini, t_token *token)
{
	char	*delimiter;

	g_sig.heredoc_flag = 1;
	delimiter = token->content;
	mini->heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (mini->heredoc_fd == -1)
		return ;
	if (here_doc_loop(mini, token, delimiter))
		return ;
	ft_close(mini->heredoc_fd);
	here_doc_end(mini);
}
