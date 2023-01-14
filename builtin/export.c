/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:46:45 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/13 21:49:45 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "return.h"
#include "ds_envp.h"

t_error	print_envp(t_envp *envp);

static int	count_argument(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_export(char **argv, t_envp *envp)
{
	int		argc;
	t_error	errno;

	if (!argv || !(*argv))
	{
		printf("ft_export argument error!\n");
		return (1);
	}
	argc = count_argument(argv);
	if (argc == 1)
		errno = print_envp(envp);
	else if (argc == 2)
		errno = set_env(envp, argv[1], NULL);
	else
		errno = set_env(envp, argv[1], argv[2]);
	if (errno)
		return (1);
	return (0);
}
