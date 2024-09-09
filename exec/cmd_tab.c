/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:48:09 by etakaham          #+#    #+#             */
/*   Updated: 2024/09/09 23:22:55 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tab(t_token *start)
{
	t_token	*token;
	int		i;

	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	return (i);
}

char	**cmd_tab(t_token *start, t_mini *mini)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	i = count_tab(start);
	tab = (char **)my_calloc(i, sizeof(char *), mini->m_node);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->content;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i] = token->content;
		token = token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
