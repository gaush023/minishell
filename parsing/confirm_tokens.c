/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirm_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:20 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/02 21:37:35 by etakaham         ###   ########.fr       */
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
			token->content = ft_strdup(tmp_str);
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
	tmp->content = ft_strdup("cat");
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

t_token	*confirm_final_orders(t_token *token, t_mini *mini)
{
	t_token	*tmp;
	t_token *tmp2;
	int		is_correct;

	tmp2 = NULL;
	is_correct = 0;
	while (token->next)
	{
		if (token->type == TRUNC || token->type == APPEND || token->type == INPUT || token->type == HERE_DOC)
		{
			printf("token:%s\n", token->content);
			tmp = token;
			if ((token->prev && token->prev->type != PIPE) && (token->next->next && token->next->next->type != PIPE))
			{
				is_correct = 2;
				token->prev->next = token->prev->next->next->next;
				token->next->next->prev = token->prev;
			}
			else if (token->next->next && token->next->next->type != PIPE)
			{
				is_correct = 2;
				token->next->next->prev = NULL;
			}
			else if (token->prev && token->prev->type != PIPE)
			{
				token = token->prev;
				is_correct = 2;
				break ;
			}
		}
		if (token->type == PIPE)
		{
			printf("pipe:%s\n", token->content);
			tmp2 = token;
			break ;
		}
		token = token->next;
	}
	if (is_correct == 2)
	{
		if (tmp2)
		{
			token->prev->next = tmp;
			tmp->prev = token->prev;
			tmp->next->next = token;
			tmp2->prev = tmp->next;
			token = token->next;
			printf("token is %s\n", token->content);
			token = confirm_final_orders(token, mini);
		}
		else
		{
			token->next = tmp;
			tmp->prev = token;
			tmp->next->next = tmp2;
		}
	}
	while (token->prev != NULL)
		token = token->prev;
	while (token->next)
	{
		set_type(token);
		token = token->next;
		set_type(token);
	}
	while (token->prev)
		token = token->prev;
	return (token);
}

t_token	*confirm_tokens(t_token *token, t_mini *mini)
{
	t_token	*tmp;
	t_token	*final_orders;

	tmp = token;
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
	final_orders = confirm_final_orders(token, mini);
	while (token->prev)
	{
		token = token->prev;
	}
	// while (token)
	// {
	// 	if (token->prev && token->prev->content) printf("prev   : %s\t", token->prev->content);
	// 	else printf("prev   : NULL\t");
	// 	if (token->content) printf("content: %s\t", token->content);
	// 	else printf("content: NULL\t");
	// 	if (token->next && token->next->content) printf("next   : %s\n", token->next->content);
	// 	else printf("next   : NULL\n");
	// 	token = token->next;
	// }
	return (token);
}
