/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:46:45 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 13:37:19 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "return.h"
#include "ds_envp.h"
#include "libft.h"

int	print_envp(t_envp *envp);

static bool	is_valid_key(char *key)
{
	if (ft_strcmp(key, "") == 0
		|| ft_strchr(key, '\"')
		|| ft_strchr(key, '\'')
		|| ft_strchr(key, ' '))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (false);
	}
	return (true);
}

static t_error	check_argument(char *arg, t_envp *envp)
{
	char	*key;

	if (ft_strchr(arg, '=') == 0)
	{
		if (is_valid_key(arg) == false)
			return (FAIL);
		else if (search_key_enode(envp, arg))
			return (SCS);
		else
			return (set_env(envp, arg, NULL));
	}
	if (get_key(arg, &key)
		|| is_valid_key(key) == false)
	{
		free(key);
		return (FAIL);
	}
	free(key);
	return (set_export(envp, arg));
}

int	ft_export(char **argv, t_envp *envp)
{
	t_error	errno;

	errno = 0;
	if (!argv || !(*argv))
	{
		printf("ft_export argument error!\n");
		return (1);
	}
	argv++;
	if (!(*argv))
		return (print_envp(envp));
	while (*argv)
	{
		if (check_argument(*argv, envp) != SCS)
			errno = 1;
		argv++;
	}
	return (errno);
}
