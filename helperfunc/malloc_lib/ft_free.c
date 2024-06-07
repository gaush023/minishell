/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:47:38 by etakaham          #+#    #+#             */
/*   Updated: 2024/05/26 19:47:38 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"

int	ft_free(void *ptr, t_node *node)
{
	if (ptr == NULL)
		return (1);
	while (node)
	{
		if (node->ptr == ptr)
		{
			if (node->is_free == true)
				return (1);
			node->is_free = true;
			break ;
		}
		node = node->next;
	}
	if (node == NULL)
		return (1);
	free(ptr);
	ptr = NULL;
	return (0);
}
