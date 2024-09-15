/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/09/16 04:37:02 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_pipe(t_token *token)
{
	t_token	*tmp;

	while (token->prev)
		token = token->prev;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	exec_cmd_fininsh(t_mini *mini, char **cmd)
{
	if (cmd)
		free_tab(cmd, mini->m_node);
	ft_close(mini->pipein);
	ft_close(mini->pipeout);
	mini->pipein = -1;
	mini->pipeout = -1;
	mini->charge = 0;
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;
	int		flag;

	flag = g_sig;
	if (mini->charge == 0)
		return ;
	cmd = cmd_tab(token, mini);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expasions(cmd[i], mini, mini->env);
		i++;
	}
	cmd[i] = NULL;
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		mini_exit(mini, cmd, 1);
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = exec_builtin(cmd, mini);
	else if (cmd)
		mini->ret = exec_bin(cmd, mini->env, mini);
	if (token->next && ft_strcmp(token->next->content, "<<") == 0
		&& flag == SIGNAL_INT)
		mini->ret = 130;
	exec_cmd_fininsh(mini, cmd);
}
