/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:31:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/25 21:32:29 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	nb_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

static bool	is_echo_option(char *s)
{
	size_t	i;

	if (ft_strncmp(s, "-n", 2))
	{
		i = 2;
		while (s[i])
		{
			if (s[i] != 'n')
				return (false);
			i++;
		}
	}
	else
		return (false);
	return (true);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_option;

	(void)is_echo_option;
	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
