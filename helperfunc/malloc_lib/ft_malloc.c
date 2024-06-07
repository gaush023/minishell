/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:47:45 by etakaham          #+#    #+#             */
/*   Updated: 2024/05/26 19:47:45 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"
#include <stdlib.h>

void	*ft_malloc(size_t size, t_node *node)
{
	t_node	*new_node;
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	new_node = malloc(sizeof(t_node));
	new_node->ptr = ptr;
	new_node->is_free = false;
	new_node->next = NULL;
	new_node->size = size;
	while (node->next)
		node = node->next;
	node->next = new_node;
	return (ptr);
}
