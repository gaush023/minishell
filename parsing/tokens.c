/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:07:22 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/07 18:01:57 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_tokens(char *line)
{
	t_token	*token;
	int		*str_flag;

	if (chek_prepareation(line) == NULL)
		return (NULL);
	str_flag = make_in_sq_flag(line);
	token = get_token_loops(line, str_flag);
	free(str_flag);
	token = get_tokens_finish(token);
	return (token);
}
