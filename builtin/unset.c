/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:05:36 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/13 21:51:12 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ds_envp.h"
#include "return.h"

int	ft_unset(char **argv, t_envp *envp)
{
	int		i;
	t_error	errno;

	if (!argv || !(*argv))
	{
		printf("ft_unset argument error!\n");
		return (1);
	}
	i = 0;
	while (argv[i])
	{
		errno = del_key_enode(envp, argv[i]);
		if (errno == ERROR)
			return (1);
		i++;
	}
	return (0);
}
