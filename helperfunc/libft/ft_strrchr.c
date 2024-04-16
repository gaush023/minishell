/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:15:01 by sagemura          #+#    #+#             */
/*   Updated: 2023/07/03 20:09:50 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	ssize_t	len;

	len = (ssize_t)ft_strlen(str);
	while (len >= 0)
	{
		if ((unsigned char)str[len] == (unsigned char)c)
		{
			return ((char *)&str[len]);
		}
		len--;
	}
	return (NULL);
}
