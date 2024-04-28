/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:15:05 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/30 16:18:46 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digit_count(int n)
{
	long long	ln;
	size_t		i;

	ln = (long)n;
	i = 0;
	if (n < 0)
	{
		ln = -ln;
		i++;
	}
	while (ln >= 10)
	{
		ln = ln / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	length;
	size_t	is_negative;
	long	ln;

	ln = (long)n;
	is_negative = 0;
	length = get_digit_count(n);
	ptr = (char *)malloc(sizeof(char) * (length + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[length] = '\0';
	if (ln < 0)
	{
		ptr[0] = '-';
		ln = -ln;
		is_negative = 1;
	}
	while (length-- > is_negative)
	{
		ptr[length] = (ln % 10) + '0';
		ln /= 10;
	}
	return (ptr);
}
