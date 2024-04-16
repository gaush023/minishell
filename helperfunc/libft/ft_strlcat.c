/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:37:50 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/29 17:13:46 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_dst(char *dst, size_t size)
{
	size_t	i;

	if (dst == NULL)
		i = 0;
	else
	{
		i = 0;
		while (dst[i] && i < size)
			i++;
	}
	return (i);
}

static size_t	get_src(char *dst, const char *src, size_t i, size_t size)
{
	size_t	j;

	if (src == NULL)
		j = 0;
	else
	{
		j = 0;
		while (src[j] && (i + j + 1) < size)
		{
			dst[i + j] = src[j];
			j++;
		}
	}
	return (j);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = get_dst(dst, size);
	j = get_src(dst, src, i, size);
	if (i < size)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}
