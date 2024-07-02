/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirm_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:20 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/02 16:04:14 by etakaham         ###   ########.fr       */
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

t_token *confirm_final_orders(t_token *token, t_mini *mini)
{
  t_token *tmp;
  t_token *tmp2;

  printf("start\n");
  while(token)
  {
    printf("token->content: %s\n", token->content);
    if(token->type == INPUT || token->type == APPEND || token->type == TRUNC || token->type == HERE_DOC)
    {
      tmp = token;    
      tmp->next = token->next;
      tmp2 = token->prev;
      if(token->next->next)
        token = token->next->next;;
      tmp2->next = token->prev; 
      token->prev = tmp2;
      while(token->next != NULL && token->next->type == PIPE)
        token = token->next;
    }
    token = token->next;
  }
  printf("done\n");
  while(token && token->prev != NULL)
    token = token->prev;
  while(token)
  {
    printf("aa token->content: %s\n", token->content);
    token = token->next;
  }
  exit(0);
  return (token);
}

t_token *check_double_redirect(t_token *token, t_mini *mini)
{

  while(token)
  {
    token = token->next;  
  }
  while(token && token->prev != NULL)
    token = token->prev;
  return (token);
}

t_token	*confirm_tokens(t_token *token, t_mini *mini)
{
	t_token	*tmp;

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
	token = confirm_final_orders(token, mini);
  token = check_double_redirect(token, mini);
	return (token);
}
