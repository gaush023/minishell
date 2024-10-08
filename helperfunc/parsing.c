/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:41:16 by etakaham          #+#    #+#             */
/*   Updated: 2024/09/09 14:33:50 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] != '\0' && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (line[i] == '\"' && open == 0)
			open = 1;
		else if (line[i] == '\'' && open == 0)
			open = 2;
		else if (line[i] == '\"' && open == 1)
			open = 0;
		else if (line[i] == '\'' && open == 2)
			open = 0;
		i++;
	}
	return (open);
}

int	quote_check(t_mini *mini, char *line)
{
	if (quotes(line, INT_MAX) != 0)
	{
		ft_putstr_fd("quote error\n", STDERR);
		my_free(line, mini->m_node);
		mini->ret = 1;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

bool	check_line_helper(t_token *token, t_mini *mini)
{
	if (is_types(token, "HTAI"))
	{
		if (token->next == NULL || is_types(token->next, "HTAIPE"))
		{
			if (token->type == HERE_DOC && token->next == NULL)
			{
				token->next = my_calloc(1, sizeof(t_token), mini->m_node);
				token->next->type = ARG;
				token->next->content = my_strdup("\0", mini->m_node);
				token->next->prev = token;
				while (token->prev)
					token = token->prev;
				mini->start = token;
				return (false);
			}
			return (true);
		}
	}
	return (false);
}

bool	check_line_helper2(t_token *token)
{
	if (token->qute_flag == 1 && token->type != ARG)
		token->type = CMD;
	if (is_types(token, "PE"))
	{
		if (!token->prev || !token->next || is_types(token->prev, "TAIPE"))
			return (true);
	}
	return (false);
}

int	check_line(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (check_line_helper(token, mini))
		{
			ft_putstr_fd(SYNTAX_ERR, STDERR);
			if (token->next)
				ft_putstr_fd(token->next->content, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putstr_fd("'\n", STDERR);
			mini->ret = 2;
			return (0);
		}
		if (check_line_helper2(token))
		{
			ft_putstr_fd(SYNTAX_ERR, STDERR);
			ft_putstr_fd(token->content, STDERR);
			write(STDERR, "'\n", 2);
			mini->ret = 2;
			return (0);
		}
		token = token->next;
	}
	return (1);
}
