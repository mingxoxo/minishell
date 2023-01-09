/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:46:45 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/09 20:27:01 by wonyang          ###   ########seoul.kr  */
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

t_error	ft_export(char **argv, t_envp *envp)
{
	int		argc;

	if (!argv || !(*argv))
	{
		printf("ft_export argument error!\n");
		return (FAIL);
	}
	argc = count_argument(argv);
	if (argc == 1)
		return (print_envp(envp));
	if (argc == 2)
		return (set_env(envp, argv[1], NULL));
	return (set_env(envp, argv[1], argv[2]));
}
