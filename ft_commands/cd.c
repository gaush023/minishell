/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:22:49 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/07 16:02:03 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		go_to_path(int opt, t_env *env);
char	*get_env_path(t_env *env, char *var, int len);
int		update_oldpwd(t_env *env);

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", STDERR);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", STDERR);
	else
	{
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(args[1], STDERR);
	ft_putstr_fd("\n", STDERR);
}

char	*make_home_path(char **args, t_env *env)
{
	char	*path;
	char	*home_path;
	char	*temp;

	home_path = get_env_path(env, "HOME", 4);
	if (!home_path)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR);
		return (NULL);
	}
	if (args[1][1] != '/')
		path = ft_strjoin(home_path, "/");
	else
		path = ft_strdup(home_path);
	temp = ft_strjoin(path, args[1] + 1);
	free(path);
	path = temp;
	free(home_path);
	return (path);
}

int	make_hyphen_path(t_env *env, char *path)
{
	int	ret;

	update_oldpwd(env);
	ret = chdir(path);
	if (ret < 0)
	{
		ret *= -1;
		print_error((char *[2]){"cd", path});
	}
	return (ret);
}

int	ft_cd(char **args, t_env *env)
{
	int		cd_ret;
	char	*path;

	if (!args[1])
		return (go_to_path(0, env));
	path = NULL;
	if (args[1][0] == '~')
	{
		path = make_home_path(args, env);
		if (path == NULL)
			return (ERR);
	}
	else
		path = ft_strdup(args[1]);
	if (ft_strcmp(path, "-") == 0)
		cd_ret = go_to_path(1, env);
	else
		cd_ret = make_hyphen_path(env, path);
	free(path);
	return (cd_ret);
}
