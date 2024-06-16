/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:17:36 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/16 01:37:24 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_next_quote(int *quote_flag, int pos)
{
	int	i;

	i = pos++;
	while (quote_flag[i] != -3)
	{
		if (quote_flag[i] == -2)
			return (1);
		if (quote_flag[i] == -1)
			return (0);
		i++;
	}
	return (0);
}

t_token	*make_token(char *str, t_token *prev_token, int *quote_flag,
		t_mini *mini)
{
	int pos;
	t_token	*token;
	t_token	*tmp;
	char	*tmp_str;

	pos = mini->pos;
	tmp_str = str;
	token = my_calloc(1, sizeof(t_token), mini->m_node);
	token->prev = prev_token;
	if (quote_flag[pos] == -2)
	{
		if (quote_flag[pos + 1] && quote_flag[pos + 1] == -2)
			token->qute_flag = 1;
		else
			token->qute_flag = 0;
	}
	if (is_next_quote(quote_flag, pos) == 1)
		token->qute_flag = 1;
	else
		token->qute_flag = 0;
	token->content = my_strdup(str, mini->m_node);
	token->next = NULL;
	my_free(str, mini->m_node);
	return (token);
}
