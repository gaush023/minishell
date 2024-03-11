/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 22:42:37 by sagemura          #+#    #+#             */
/*   Updated: 2024/03/11 17:28:52 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_type(t_token *token, int type)
{
	if(token && token->type == type)
		return(1);
	else
		return(0);
}

int is_types(t_token *token, char *types)
{
	if(ft_strchr(types, ' ') && is_type(token, EMPTY))
		return(1);
	else if(ft_strchr(types, 'X') && is_type(token, CMD))
		return(1);
	else if(ft_strchr(types, 'x') && is_type(token, ARG))
		return(1);
	else if(ft_strchr(types, 'R') && is_type(token, REDIR))
		return(1);
	else if(ft_strchr(types, 'A') && is_type(token, APPEND))
		return(1);
	else if(ft_strchr(types, 'I') && is_type(token, INPUT))
		return(1);
	else if(ft_strchr(types, 'P') && is_type(token, PIPE))
		return(1);
	else if(ft_strchr(types, 'E') && is_type(token, SEMICOLON))
		return(1);
	return(0);
}