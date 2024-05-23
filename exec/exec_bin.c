/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/05/13 20:20:28 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	magic_box(char *path, char **args, t_env *env, t_mini *mini)
{
	char	**env_array;
	int		ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		env_array = env_to_array(env);
		if (ft_strchr(path, '/') != NULL)
    {
      printf("path: %s\n", path);
      if(g_sig.heredoc_flag == 1)
      {
        printf("heredoc_flag: %d\n", g_sig.heredoc_flag);
        printf("path: %s\n", path);
        printf("mini->start->content: %s\n", mini->start->content);
        g_sig.heredoc_flag = 0;
        return (-1);
      }
      execve(path, args, env_array);
    }
		ret = error_msg(path);
		free_tab(env_array);
		free_token(mini->start, mini->flag);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.sig_flag);
	if (ret == 32256 || ret == 32512)
		ret = ret / 256;
	else
		ret = !!ret;
	return (ret);
}

char	*path_join(const char *s1, char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_free(tmp);
	return (path);
}

char	*check_dir(char *bin, char *cmd)
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
			path = path_join(bin, item->d_name);
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
		return (magic_box(args[0], args, env, mini));
	bin = ft_split(env->value, ':');
	if (!args[0] || !bin[0])
		return (ERR);
	i = 0;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (path != NULL)
		ret = magic_box(path, args, env, mini);
	else
		ret = magic_box(args[0], args, env, mini);
	free_tab(bin);
	ft_free(path);
	return (ret);
}
