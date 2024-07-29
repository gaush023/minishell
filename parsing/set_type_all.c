/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:05:45 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/29 10:50:14 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*set_type_all(t_token *token)
{
	while (token->prev != NULL)
	{
		set_type(token);
		token = token->prev;
	}
	set_type(token);
	return (token);
}
