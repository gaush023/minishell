/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:48:14 by etakaham          #+#    #+#             */
/*   Updated: 2024/05/26 19:48:14 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"

static void	*element_cpy(void *dest, const void *src, t_node *node)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (src == NULL && dest == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (node)
	{
		if (node->ptr == src)
			break ;
		node = node->next;
	}
	i = 0;
	while (i < node->size)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t size, t_node *node)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (ft_calloc(size, 1, node));
	if (size == 0)
	{
		ft_free(ptr, node);
		return (NULL);
	}
	new_ptr = ft_calloc(size, 1, node);
	if (new_ptr == NULL)
		return (NULL);
	element_cpy(new_ptr, ptr, node);
	ft_free(ptr, node);
	return (new_ptr);
}
