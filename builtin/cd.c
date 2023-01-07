/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:36:28 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/06 22:45:32 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

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
		return (-1);
	return (0);
}

static int	move_path(char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("bash: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

// cd : env에서 HOME 경로로 이동
// cd . :
// cd .. :
// cd /경로 : 
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
	return (move_path(path));
}
