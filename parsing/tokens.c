/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:07:22 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/09 18:40:46 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_tokens(char *line, t_mini *mini)
{
	t_token	*token;
	int		*str_flag;

	if (line == NULL || chek_prepareation(line) == NULL)
		return (NULL);
	line = my_strjoin(" ", line, mini->m_node);
	str_flag = make_in_sq_flag(line, mini);
	token = get_token_loops(line, str_flag, mini);
	my_free(str_flag, mini->m_node);
	token = get_tokens_finish(token, mini);
	t_token *tmp = token;
	printf("\n=========tokens==============\n");
	while(tmp)
	{
		printf("content: %s\n", tmp->content);
		printf("type: %d\n", tmp->type);
		tmp = tmp->next;
	}
	printf("=============================\n");
	return (token);
}
