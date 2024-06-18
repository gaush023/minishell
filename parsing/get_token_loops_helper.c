/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_loops_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:05:45 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/18 20:56:37 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cutout_str(char *line, unsigned int i, unsigned int k, t_mini *mini);

void	get_token_loops_helper(t_args *a)
{
	char	*tmp_str;
	int		k;

	k = a->i;
	while (a->flag[a->i] == 0)
		a->i++;
	a->mini->pos = a->i;
	tmp_str = cutout_str(a->l, a->i, k, a->mini);
	if (tmp_str[0] == EXPANSION)
	{
		tmp_str++;
		if (ft_strcmp(tmp_str, "EMPTY") != 0)
		{
			tmp_str = cutout_str(a->l, a->i, k, a->mini);
			a->token = make_token(tmp_str, a->tmp_t, a->flag, a->mini);
			a->tmp_t = a->token;
		}
		else
			my_free(tmp_str, a->mini->m_node);
	}
	else
	{
		a->token = make_token(tmp_str, a->tmp_t, a->flag, a->mini);
		a->tmp_t = a->token;
	}
}
