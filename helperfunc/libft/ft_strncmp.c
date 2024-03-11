/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:05:24 by sagemura          #+#    #+#             */
/*   Updated: 2024/03/07 23:56:12 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n-- && *s1 && *s2 && *s1 == *s2)
    {
	s1++;
	s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

