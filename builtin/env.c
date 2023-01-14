/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:40:20 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/13 21:47:59 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "return.h"
#include "ds_envp.h"
#include "libft.h"

int	ft_env(char **argv, t_envp *envp)
{
	char	**arr;
	int		i;

	if (!argv || !(*argv))
	{
		printf("ft_env argument error!\n");
		return (1);
	}
	if (argv[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (1);
	}
	arr = envp->arr;
	i = 0;
	while (arr[i])
	{
		ft_putendl_fd(arr[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
