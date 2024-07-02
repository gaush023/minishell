/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:06:41 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/13 16:08:07 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*my_readline(const char *prompt, t_node *node, t_mini *mini)
{
	char	*str;
	char	*str_cpy;

	str = readline(prompt);
	if(!str && g_sig == ON_HERE_DOC)
    return (NULL);
  if (!str)
		my_exit(mini->ret, node);
	str_cpy = my_strdup(str, node);
  my_free(str, node);
	return (str_cpy);
}
