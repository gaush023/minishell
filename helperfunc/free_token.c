/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:45:56 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/20 18:21:37 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token && token->next)
	{
		tmp = token->next;
		ft_free(token->content);
		ft_free(token->prev);
		token = tmp;
	}
	ft_free(token->content);
}
