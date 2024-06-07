/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:47:26 by etakaham          #+#    #+#             */
/*   Updated: 2024/05/26 19:47:26 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)b;
	while (i < len)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (tmp);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size, t_node *node)
{
	void	*ptr;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	if (size * count == 0)
		return (NULL);
	ptr = ft_malloc(count * size, node);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
