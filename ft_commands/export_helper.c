/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/09/12 14:41:59 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_only_number(const char *str)
{
	if (ft_isdigit(*str))
		return (true);
	while (*str)
	{
		if (*str == '=')
			break ;
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	is_include_equal(const char *str)
{
	if (is_only_number(str))
		return (-1);
	if (*str == '=')
		return (-1);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '=')
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
