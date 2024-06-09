/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:06:41 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/09 20:23:54 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*my_readline(const char *prompt, t_node *node)
{
	char	*str;
	char	*str_cpy;

	str = readline(prompt);
	if (!str)
	{
		write(2, "exit\n", 5);
		my_exit(1, node);
	}
	str_cpy = my_strdup(str, node);
	free(str);
	return (str_cpy);
}
