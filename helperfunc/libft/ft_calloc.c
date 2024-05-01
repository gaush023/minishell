/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:26:51 by sagemura          #+#    #+#             */
/*   Updated: 2024/05/01 09:15:40 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	if (nitems && size > SIZE_MAX / nitems)
		return (NULL);
	if (size * nitems == 0)
	{
		size = 1;
		nitems = 1;
	}
	ptr = malloc(nitems * size);
	if (ptr == NULL)
		exit(1);
	ft_bzero(ptr, size * nitems);
	return (ptr);
}
