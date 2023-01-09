/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:15:07 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/09 17:07:58 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"

static bool	is_valid_argument(char *arg)
{
	if (!arg)
		return (true);
	return (ft_isinteger(arg));
}

static int	count_argument(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_exit(char **argv)
{
	if (!argv || !(*argv))
	{
		printf("ft_exit argument error!\n");
		return (-1);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	if (is_valid_argument(argv[1]) == false)
	{
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
		return (-1);
	}
	if (count_argument(argv) > 2)
	{
		ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
		return (0);
	}
	if (count_argument(argv) == 2)
		exit(ft_atoi(argv[1]));
	return (0);
}
