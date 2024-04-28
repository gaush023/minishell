/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:27:47 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/27 17:06:06 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_start(const char *s, const char *charset)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (charset[j])
		{
			if (s[i] == charset[j])
				break ;
			j++;
		}
		if (!charset[j])
			break ;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = get_start(s1, set);
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	ptr = malloc(end - start + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1 + start, end - start);
	ptr[end - start] = '\0';
	return (ptr);
}
