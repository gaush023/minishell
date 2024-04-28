/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:56:34 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/27 17:49:09 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	unsigned char		*uc_str1;
	unsigned const char	*uc_str2;

	uc_str1 = (unsigned char *)str1;
	uc_str2 = (unsigned const char *)str2;
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (uc_str1 < uc_str2)
	{
		uc_str1 = ft_memcpy(str1, str2, n);
	}
	else
	{
		while (n--)
		{
			uc_str1[n] = uc_str2[n];
		}
	}
	return (uc_str1);
}
