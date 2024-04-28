/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:43:41 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/30 16:20:21 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	unsigned const char	*u_str;
	unsigned char		u_c;

	u_str = (unsigned char *)str;
	u_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (u_str[i] == u_c)
			return ((void *)&u_str[i]);
		i++;
	}
	return (0);
}
