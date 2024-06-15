/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:22:49 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/16 00:29:11 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*make_home_path(char **args, t_mini *mini)
{
	char	*path;
	char	*home_path;
	char	*temp;

	home_path = get_env_path(mini->env, "HOME", 4);
	if (!home_path)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR);
		return (NULL);
	}
	if (args[1][1] != '/')
		path = my_strjoin(home_path, "/", mini->m_node);
	else
		path = my_strdup(home_path, mini->m_node);
	temp = my_strjoin(path, args[1] + 1, mini->m_node);
	my_free(path, mini->m_node);
	path = temp;
	my_free(home_path, mini->m_node);
	return (path);
}

int	make_hyphen_path(t_mini *mini, char *path)
{
	int	ret;

	update_oldpwd(mini);
	ret = chdir(path);
	if (ret < 0)
	{
		ret *= -1;
		print_error((char *[2]){"cd", path});
	}
	return (ret);
}

int	ft_cd(char **args, t_mini *mini)
{
	int		cd_ret;
	char	*path;

	if (!args[1])
		return (go_to_path(0, mini));
	path = NULL;
	if (args[1][0] == '~')
	{
		path = make_home_path(args, mini);
		if (path == NULL)
			return (ERR);
	}
	else
		path = ft_strdup(args[1]);
	if (ft_strcmp(path, "-") == 0)
		cd_ret = go_to_path(1, mini);
	else
		cd_ret = make_hyphen_path(mini, path);
	my_free(path, mini->m_node);
	return (cd_ret);
}
