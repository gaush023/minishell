/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/08/27 19:52:28 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_include_equal(const char *str)
{
	if (*str == '=')
		return (-1);
	while (*str)
	{
		if (*str == '-' || *str == '+' || ft_isdigit(*str))
			return (-1);
		if (*str == '=')
			break ;
		str++;
	}
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (*str == '=')
			return (0);
		str++;
	}
	return (0);
}

bool	is_env_format(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			return (false);
		if (str[i] == '=')
			break ;
		i++;
	}
	return (true);
}
