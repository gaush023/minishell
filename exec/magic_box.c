/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/08/27 20:01:29 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	calc_ret(int ret)
{
	if (ret == 32256 || ret == 32512)
		ret = ret / 256;
	else
		ret = !!ret;
	if (g_sig == SIGNAL_INT || g_sig == SIGNAL_QUIT)
		ret = g_sig;
	return (ret);
}

int	magic_box(char *path, char **args, t_env *env, t_mini *mini)
{
	char	**env_array;
	int		ret;
	int		pid;

	ret = SUCCESS;
	g_sig = ON_PID;
	pid = fork();
	if (pid == 0)
	{
		g_sig = SIGNAL_OFF;
		env_array = env_to_array(env, mini);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_msg(path, mini);
		free_tab(env_array, mini->m_node);
		free_token(mini->start, mini->flag, mini->m_node);
		my_exit(ret, mini->m_node);
	}
	else
		waitpid(pid, &ret, 0);
	return (calc_ret(ret));
}
