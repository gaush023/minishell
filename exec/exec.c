/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/03/25 03:38:53 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < REDIR)
	{
		token = token->next;
		i++;
	}
	if (!(tab = (char **)malloc(sizeof(char *) * i)))
		return (NULL);
	token = start->next;
	tab[0] = start->content;
	i = 1;
	while (token && token->type < REDIR)
	{
		tab[i] = token->content;
		token = token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char *cmd;
	int i;

	if (mini->charge == 0)
		return ;
	cmd = cmd_tab(token);
    i = 0;
    while(cmd && cmd[i])
    {
        cmd[i] = expasions(cmd[i], mini->env, mini->ret);
        i++;
    }
    
}