/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:32:41 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/30 18:43:38 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	add_numbers(long res, int digit, int sign, int *flg)
{
	if (sign == 1 && res > (LONG_MAX - digit) / 10)
	{
		*flg = 1;
		return (LONG_MAX);
	}
	else if (sign == -1 && res * -1 < (LONG_MIN + digit) / 10)
	{
		*flg = 1;
		return (LONG_MIN);
	}
	else
		return (res * 10 + digit);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	long	res;
	int		flg;

	flg = 0;
	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = add_numbers(res, str[i] - '0', sign, &flg);
		if (flg == 1)
			return (res);
		i++;
	}
	return (sign * res);
}
