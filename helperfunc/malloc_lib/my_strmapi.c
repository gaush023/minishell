/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:47:35 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/07 17:24:10 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"

static size_t	my_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*my_strmapi(const char *s, char (*f)(unsigned int, char), t_node *node)
{
	char			*new_str;
	unsigned int	length;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	length = my_strlen(s);
	new_str = my_calloc(length + 1, sizeof(char), node);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < length)
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	return (new_str);
}
