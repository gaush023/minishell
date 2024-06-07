/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:44:58 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/07 17:23:00 by etakaham         ###   ########.fr       */
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

char	*my_strdup(const char *s1, t_node *node)
{
	size_t	len;
	size_t	i;
	char	*s2;

	len = my_strlen(s1);
	s2 = my_calloc(len + 1, sizeof(char), node);
	if (!s2)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
