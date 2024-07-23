/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirm_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:20 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/23 22:49:16 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*confrim_tokens_prepareation(t_token *token, t_mini *mini)
{
	t_token	*tmp;
	char	*tmp_str;

	while (token->next != NULL)
	{
		if (token->qute_flag == 1 && token->type == ARG
			&& token->next->qute_flag == 1 && token->next->type == ARG)
		{
			tmp_str = ft_strjoin(token->content, token->next->content);
			token->content = my_strdup(tmp_str, mini->m_node);
			my_free(tmp_str, mini->m_node);
			token->qute_flag = token->next->qute_flag;
			tmp = token->next;
			token->next = tmp->next;
		}
		else if (token->next != NULL)
			token = token->next;
	}
	while (token->prev != NULL)
		token = token->prev;
	return (token);
}

t_token	*add_infront_cat(t_token *token, t_mini *mini)
{
	t_token	*tmp;

	tmp = my_calloc(1, sizeof(t_token), mini->m_node);
	tmp->content = my_strdup("cat", mini->m_node);
	tmp->type = CMD;
	tmp->next = token;
	tmp->prev = NULL;
	token->prev = tmp;
	token = token->prev;
	return (token);
}

t_token	*changes_orders_heredoc(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = NULL;
	tmp = token->next->next;
	tmp->type = CMD;
	tmp->prev = NULL;
	tmp2 = token->next->next->next;
	token->next->next = tmp2;
	token->prev = tmp;
	tmp->next = token;
	tmp->prev = NULL;
	token = token->prev;
	return (token);
}

static bool	confirm_tokens_helper(t_token *token, t_mini *mini)
{
	if ((token->type == HERE_DOC || ft_strcmp(token->content, ">") == 0)
		&& token->next == NULL)
	{
		free_token(token, 0, mini->m_node);
		ft_putstr_fd("minishell: syntax error: unexpected \'newline\'\n", 2);
		mini->ret = 2;
		return (false);
	}
	return (true);
}

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

t_token	*confirm_final_orders(t_token *token, t_mini *mini)
{
	t_token	*copied_two_tokens;
	t_token	*tmp2;

	while (token && token->next != NULL)
	{
		if (token->type == INPUT || token->type == APPEND
			|| token->type == TRUNC || token->type == HERE_DOC)
		{
			copied_two_tokens = copy_two_tokens(token, mini);
			if (!copied_two_tokens)
				return (token);
			if (token->next->next != NULL)
				tmp2 = token->next->next;
			else
				break ;
			if (token->prev != NULL)
			{
				token = token->prev;
				token->next = tmp2;
				tmp2->prev = token;
			}
			else
			{
				token = tmp2;
				token->prev = NULL;
			}
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
				break ;
			}
		}
		token = token->next;
	}
	token = set_type_all(token);
	return (token);
}

t_token	*confirm_tokens(t_token *token, t_mini *mini)
{
	t_token	*new_token_list;

	token = confrim_tokens_prepareation(token, mini);
	if (!confirm_tokens_helper(token, mini))
		return (NULL);
	if (token->type == HERE_DOC && token->qute_flag == 0)
	{
		if (!token->next->next || token->next->next->type != ARG)
			return (add_infront_cat(token, mini));
		else if (token->next->next->type == ARG)
			return (changes_orders_heredoc(token));
	}
	else if (token->type == HERE_DOC && (token->qute_flag == 1))
	{
		ft_putstr_fd("minishell: command not found: <<\n", 2);
		free_token(token, 0, mini->m_node);
		token = NULL;
	}
	new_token_list = confirm_final_orders(token, mini);
	return (new_token_list);
}
