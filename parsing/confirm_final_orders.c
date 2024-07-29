/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirm_final_orders.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:20 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/25 13:50:43 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*copy_two_tokens(t_token *token, t_mini *mini)
{
	t_token	*count_tokens;
	int		len;
	t_token	*tmp;

	count_tokens = token;
	len = 0;
	while (count_tokens && len < 2)
	{
		count_tokens = count_tokens->next;
		len++;
	}
	if (len < 1)
		return (NULL);
	tmp = my_calloc(1, sizeof(t_token), mini->m_node);
	tmp->content = my_strdup(token->content, mini->m_node);
	tmp->type = token->type;
	tmp->next = my_calloc(1, sizeof(t_token), mini->m_node);
	tmp->next->prev = tmp;
	tmp->next->type = token->next->type;
	tmp->next->content = my_strdup(token->next->content, mini->m_node);
	return (tmp);
}

static t_token	*cutout_two_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = token->next->next;
	if (token->prev != NULL)
	{
		token = token->prev;
		token->next = tmp;
		tmp->prev = token;
	}
	else
	{
		token = tmp;
		token->prev = NULL;
	}
	return (token);
}

static t_token	*add_two_tokens_last(t_token *token, t_token *copied_two_tokens)
{
	while (token->next && token->next->type != PIPE)
		token = token->next;
	if (token->next && token->next->type == PIPE)
	{
		copied_two_tokens->next->next = token->next;
		token->next = copied_two_tokens;
		while (token->next->type != PIPE)
			token = token->next;
	}
	else
	{
		token->next = copied_two_tokens;
		copied_two_tokens->prev = token;
		token->next->next->next = NULL;
	}
	return (token);
}

t_token	*confirm_final_orders(t_token *token, t_mini *mini)
{
	t_token	*copied_two_tokens;

	while (token && token->next != NULL)
	{
		if (token->type == INPUT || token->type == APPEND
			|| token->type == TRUNC || token->type == HERE_DOC)
		{
			copied_two_tokens = copy_two_tokens(token, mini);
			if (token->next->next != NULL && copied_two_tokens)
				token = cutout_two_tokens(token);
			else
				break ;
			token = add_two_tokens_last(token, copied_two_tokens);
		}
		token = token->next;
	}
	token = set_type_all(token);
	return (token);
}
