/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/09/09 14:32:52 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	error_msg_helper(char *path, int fd, DIR *folder)
{
	int	ret;

	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UK_CMD;
	else
		ret = IS_DIR;
	return (ret);
}

int	error_msg(char *path, t_mini *mini)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putstr_fd(" :command not found", STDERR);
	else if (fd == -1 && folder == NULL && mini->is_printable == 0)
	{
		ft_putstr_fd(": No such file or directory", STDERR);
		mini->is_printable = 1;
	}
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd(": Permission denied", STDERR);
	ft_putstr_fd("\n", STDERR);
	ret = error_msg_helper(path, fd, folder);
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}
