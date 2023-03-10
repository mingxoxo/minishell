/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:08:57 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/16 16:32:32 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include "return.h"

t_error	ft_dup2(int fd1, int fd2)
{
	if (close(fd2) == -1)
		return (ERROR);
	if (dup2(fd1, fd2) == -1)
		return (ERROR);
	if (close(fd1) == -1)
		return (ERROR);
	return (SCS);
}

bool	is_directory(char *path)
{
	struct stat	file_info;

	if (lstat(path, &file_info) < 0)
		return (false);
	if ((S_IFMT & file_info.st_mode) == S_IFDIR)
		return (true);
	return (false);
}
