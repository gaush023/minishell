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

void	free_token(t_token *start, int flag)
{
  if(start == NULL)
    return ;
	while (start && start->next)
	{
		ft_free(start->content);
		start = start->next;
		ft_free(start->prev);
	}
	if (start && (flag != 1 || ft_strcmp(start->content,
				"exit") == 0))
	{
		ft_free(start->content);
		ft_free(start);
	}
}
