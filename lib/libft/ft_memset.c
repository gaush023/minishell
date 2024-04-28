/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:26:53 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/26 18:39:03 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*n_str;

	i = 0;
	n_str = (unsigned char *)str;
	while (i < n)
	{
		n_str[i] = (unsigned char)c;
		i++;
	}
	return (n_str);
}
