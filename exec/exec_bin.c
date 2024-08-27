/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/08/27 20:03:52 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	exec_bin_error_msg(char **args)
{
	write(2, "minishell: ", 11);
	write(2, args[0], ft_strlen(args[0]));
	write(2, ": No such file or directly\n", 27);
	return (127);
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
		return (exec_bin_error_msg(args));
	bin = my_split(env->value, ':', mini->m_node);
	if (!args[0] || !bin[0])
		return (ERR);
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
