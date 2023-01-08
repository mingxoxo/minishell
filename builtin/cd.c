/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:36:28 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/07 14:39:46 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

static int	path_error(char *path)
{
	ft_putstr_fd("bash: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (-1);
}

// todo : getenv를 내장 환경변수로 변경
static int	move_home(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
		return (-1);
	}
	if (chdir(path) != 0)
		return (path_error(path));
	return (0);
}

static int	move_path(char *path)
{
	if (chdir(path) != 0)
		return (path_error(path));
	return (0);
}

// todo : getenv를 내장 환경변수로 변경
static int	move_oldpwd(void)
{
	char	*path;

	path = getenv("OLDPWD");
	if (!path)
	{
		ft_putendl_fd("bash: cd: OLDPWD not set", STDERR_FILENO);
		return (-1);
	}
	if (chdir(path) != 0)
		return (path_error(path));
	ft_putendl_fd(path, STDOUT_FILENO);
	return (0);
}

int	ft_cd(char **argv)
{
	char	*path;
	
	if (!argv || !(*argv))
	{
		printf("ft_cd argument error!\n");
		return (-1);
	}
	path = argv[1];
	if (!path)
		return (move_home());
	if (ft_strcmp(path, ".") == 0)
		return (0);
	if (ft_strcmp(path, "-") == 0)
		return (move_oldpwd());
	return (move_path(path));
}
