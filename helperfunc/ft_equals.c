/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_equals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:48:36 by etakaham          #+#    #+#             */
/*   Updated: 2024/04/16 20:48:36 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

bool	ft_equals(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == '\n')
			return (true);
		else if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s1[i] == '\n')
		return (true);
	else if (s1[i] != s2[i])
		return (false);
	return (true);
}
