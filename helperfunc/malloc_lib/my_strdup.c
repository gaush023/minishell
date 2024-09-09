/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:44:58 by etakaham          #+#    #+#             */
/*   Updated: 2024/09/09 23:21:27 by sagemura         ###   ########.fr       */
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
	s2[i] = '\0';
	return (s2);
}
