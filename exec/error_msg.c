/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/23 17:07:20 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_msg(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putstr_fd(": command not found\n", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putstr_fd(": No such file or directory\n", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd(": is a directory\n", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd(": Permission denied\n", STDERR);
	if (ft_strchr(path, '/') != NULL || (folder != NULL && fd == -1))
		ret = UK_CMD;
	else
		ret = IS_DIR;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}
