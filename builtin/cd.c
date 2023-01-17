/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:36:28 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 13:37:20 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "libft.h"
#include "ds_envp.h"
#include "return.h"

static t_error	update_pwd(t_envp *envp)
{
	t_error	errno;
	char	*old_path;
	char	*path;

	errno = SCS;
	if (search_key_enode(envp, "OLDPWD"))
	{
		old_path = search_key_value(envp, "PWD");
		if (!old_path)
			errno = set_env(envp, "OLDPWD", "");
		else
			errno = set_env(envp, "OLDPWD", old_path);
	}
	if (errno)
		return (errno);
	if (search_key_value(envp, "PWD"))
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (ERROR);
		errno = set_env(envp, "PWD", path);
		free(path);
	}
	return (errno);
}

static t_error	path_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (access(path, F_OK) != 0)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (opendir(path) == NULL)
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	else if (access(path, X_OK) != 0)
		ft_putendl_fd(": permission denied", STDERR_FILENO);
	else
		ft_putendl_fd(": error", STDERR_FILENO);
	return (FAIL);
}

static t_error	move_home(t_envp *envp)
{
	char	*path;

	path = search_key_value(envp, "HOME");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (FAIL);
	}
	if (chdir(path) != 0)
		return (path_error(path));
	return (update_pwd(envp));
}

static t_error	move_oldpwd(t_envp *envp)
{
	char	*path;

	path = search_key_value(envp, "OLDPWD");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (FAIL);
	}
	if (chdir(path) != 0)
		return (path_error(path));
	ft_putendl_fd(path, STDOUT_FILENO);
	return (update_pwd(envp));
}

int	ft_cd(char **argv, t_envp *envp)
{
	char	*path;
	t_error	errno;

	if (!argv || !(*argv))
	{
		printf("ft_cd argument error!\n");
		return (1);
	}
	path = argv[1];
	if (!path || ft_strcmp(path, "~") == 0)
		errno = move_home(envp);
	else if (ft_strcmp(path, "-") == 0)
		errno = move_oldpwd(envp);
	else if (chdir(path) != 0)
		errno = path_error(path);
	else
		errno = update_pwd(envp);
	if (errno)
		return (1);
	return (0);
}
