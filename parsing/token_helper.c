/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:36 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/07 19:42:37 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_type(t_token *token)
{
	if (ft_strcmp(token->content, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->content, ";") == 0)
		token->type = END;
	else if (ft_strcmp(token->content, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->content, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->content, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->content, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->content, "<<") == 0)
		token->type = HERE_DOC;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*make_token(char *str, t_token *prev_token, int *quote_flag, int pos, t_mini *mini)
{
	t_token	*token;
	t_token	*tmp;
	int		i;

	token = my_calloc(1, sizeof(t_token), mini->m_node);
	token->prev = prev_token;
	if (quote_flag[pos] == -2)
	{
		i = pos;
		if (quote_flag[pos + 1] && quote_flag[pos + 1] == -2)
			token->qute_flag = 1;
		else
			token->qute_flag = 0;
	}
	else
		token->qute_flag = 0;
	token->content = my_strdup(str, mini->m_node);
	token->next = NULL;
	my_free(str, mini->m_node);
	return (token);
}
