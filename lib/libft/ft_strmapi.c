/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:45:01 by sagemura          #+#    #+#             */
/*   Updated: 2023/06/30 16:46:12 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	length;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	new_str = (char *)malloc(sizeof(char) * (length + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[length] = '\0';
	return (new_str);
}
