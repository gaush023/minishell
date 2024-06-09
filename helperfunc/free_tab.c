/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:22:47 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/20 18:29:38 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tab, t_node *node)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		my_free(tab[i], node);
		i++;
	}
	my_free(tab, node);
}
