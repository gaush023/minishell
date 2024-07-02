/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/06/25 20:31:05 by sagemura         ###   ########.fr       */
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
		ret = error_msg(path);
		free_tab(env_array, mini->m_node);
		free_token(mini->start, mini->flag, mini->m_node);
		my_exit(ret, mini->m_node);
	}
	else
		waitpid(pid, &ret, 0);
	return (calc_ret(ret));
}

char	*path_join(const char *s1, char *s2, t_node *node)
{
	char	*tmp;
	char	*path;

	tmp = my_strjoin(s1, "/", node);
	path = my_strjoin(tmp, s2, node);
	my_free(tmp, node);
	return (path);
}

char	*check_dir(char *bin, char *cmd, t_mini *mini)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, cmd) == 0)
			path = path_join(bin, item->d_name, mini->m_node);
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	exec_bin(char **args, t_env *env, t_mini *mini)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = UK_CMD;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (!env || !env->next)
	{
		printf("nothing\n");
		bin = my_split(env->value, ':', mini->m_node);
	}
	bin = my_split(env->value, ':', mini->m_node);
	if (!args[0] || !bin[0])
		return (ERR);
	i = 0;
	path = check_dir(bin[0] + 5, args[0], mini);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0], mini);
	if (path != NULL)
		ret = magic_box(path, args, env, mini);
	else
		ret = magic_box(args[0], args, env, mini);
	free_tab(bin, mini->m_node);
	my_free(path, mini->m_node);
	return (ret);
}
