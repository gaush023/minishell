/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:48:17 by etakaham          #+#    #+#             */
/*   Updated: 2024/05/26 19:48:17 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"

int	malloc_end(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		if (node->size != 0 && node->is_free == false)
		{
			free(node->ptr);
		}
		tmp = node;
		node = node->next;
		free(tmp);
	}
	return (0);
}
