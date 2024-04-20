/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:34:20 by sagemura          #+#    #+#             */
/*   Updated: 2023/07/10 09:18:28 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_count(char const *s, char c)
{
	size_t	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static void	free_result_array(char **result, int count)
{
	while (count--)
		free(result[count]);
	free(result);
}

static char	*find_next_word(char const *s, char c, char **word_end)
{
	while (*s == c)
		s++;
	*word_end = ft_strchr(s, c);
	if (!*word_end)
		*word_end = ft_strchr(s, '\0');
	return ((char *)s);
}

static char	*copy_words(const char *s1, size_t n)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1);
	if (n < len)
		len = n;
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	s2 = ft_memcpy(s2, s1, len);
	s2[len] = '\0';
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;
	int		i;
	char	*word_start;
	char	*word_end;

	word_count = get_word_count(s, c);
	result = (malloc(sizeof(char *) * (word_count + 1)));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		word_start = find_next_word(s, c, &word_end);
		result[i] = copy_words(word_start, word_end - word_start);
		if (!result[i])
		{
			free_result_array(result, i);
			return (NULL);
		}
		s = word_end;
		i++;
	}
	result[i] = NULL;
	return (result);
}
