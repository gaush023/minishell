/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:41:30 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/07 17:19:52 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"

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

char	*my_itoa(int num, t_node *node)
{
	char	*num_str;
	size_t	len;
	size_t	is_neg;
	long	l_num;

	l_num = (long)num;
	is_neg = 0;
	len = get_digit_count(num);
	num_str = my_calloc(len + 1, sizeof(char), node);
	if (!num_str)
		return (NULL);
	if (l_num < 0)
	{
		num_str[0] = '-';
		l_num = l_num * -1;
		is_neg = 1;
	}
	while (len-- > is_neg)
	{
		num_str[len] = (l_num % 10) + '0';
		l_num /= 10;
	}
	return (num_str);
}
