/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:28:16 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/25 08:04:01 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t				i;
	const unsigned char	*u_str1;
	const unsigned char	*u_str2;

	u_str1 = (const unsigned char *)str1;
	u_str2 = (const unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (u_str1[i] != u_str2[i])
			return (u_str1[i] - u_str2[i]);
		i++;
	}
	return (0);
}
