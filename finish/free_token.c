/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:22:48 by sagemura          #+#    #+#             */
/*   Updated: 2024/05/01 10:55:15 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token *start, int flag, t_node *node)
{
	if (start == NULL)
		return ;
	while (start && start->next)
	{
		my_free(start->content, node);
		start = start->next;
		my_free(start->prev, node);
	}
	if (start && (flag != 1 || ft_strcmp(start->content,
				"exit") == 0))
	{
		my_free(start->content, node);
		my_free(start, node);
	}
}
