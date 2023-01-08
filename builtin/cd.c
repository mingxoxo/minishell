/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:36:28 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/08 22:58:54 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/ds_envp.h"
#include "../includes/return.h"

static t_error	update_pwd(t_envp *envp)
{
	t_error	errno;
	char	*old_path;
	char	*path;

	if (search_key_value(envp, "OLDPWD"))
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
	}
	return (errno);
}

static t_error	path_error(char *path)
{
	ft_putstr_fd("bash: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (FAIL);
}

static t_error	move_home(t_envp *envp)
{
	char	*path;

	path = search_key_value(envp, "HOME");
	if (!path)
	{
		ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
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
		ft_putendl_fd("bash: cd: OLDPWD not set", STDERR_FILENO);
		return (FAIL);
	}
	if (chdir(path) != 0)
		return (path_error(path));
	ft_putendl_fd(path, STDOUT_FILENO);
	return (update_pwd(envp));
}

t_error	ft_cd(char **argv, t_envp *envp)
{
	char	*path;

	if (!argv || !(*argv))
	{
		printf("ft_cd argument error!\n");
		return (FAIL);
	}
	path = argv[1];
	if (!path)
		return (move_home(envp));
	if (ft_strcmp(path, ".") == 0)
		return (update_pwd(envp));
	if (ft_strcmp(path, "-") == 0)
		return (move_oldpwd(envp));
	if (chdir(path) != 0)
		return (path_error(path));
	return (update_pwd(envp));
}

int	main(int c, char **a, char **m)
{
	t_envp envp;

	init_envp(&envp, m);
	print_arr((&envp)->arr);
	ft_cd(a, &envp);
	print_arr((&envp)->arr);
	printf("PWD : %s\n", search_key_value(&envp, "PWD"));
	printf("OLDPWD : %s\n", search_key_value(&envp, "OLDPWD"));
	return (0);
}
