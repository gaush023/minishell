/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:11:03 by sagemura          #+#    #+#             */
/*   Updated: 2024/07/30 03:43:55 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_msg(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putstr_fd("command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putstr_fd(": a No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd(": Permission denied", STDERR);
	ft_putstr_fd("\n", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UK_CMD;
	else
		ret = IS_DIR;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}
