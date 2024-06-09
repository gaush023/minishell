/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:57:57 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/09 18:20:20 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"

static size_t	split_len(const char *s, char c)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			len++;
		while (s[i] != c && s[i + 1] != '\0')
			i++;
		i++;
	}
	return (len);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
	{
		i++;
	}
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static int	matrix_free(char **matrix, size_t len, t_node *node)
{
	size_t	i;

	i = 0;
	while (i < len)
		my_free(matrix[i++], node);
	my_free(matrix, node);
	return (1);
}

static int	insert_str(const char *s, char c, char **res, t_node *node)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

	len = split_len(s, c);
	i = 0;
	j = 0;
	while (i < len)
	{
		res[i] = my_calloc(word_len(&s[j], c) + 1, sizeof(char), node);
		if (res[i] == NULL)
			return (matrix_free(res, i, node));
		k = 0;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j] != '\0')
			res[i][k++] = s[j++];
		res[i++][k] = '\0';
	}
	return (0);
}

char	**my_split(const char *s, char c, t_node *node)
{
	char	**result;
	size_t	len;

	len = split_len(s, c);
	result = (char **)my_calloc(len + 1, sizeof(char *), node);
	if (!result)
		return (NULL);
	if (insert_str(s, c, result, node) == 1)
		return (NULL);
	return (result);
}
