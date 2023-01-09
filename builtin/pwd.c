/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:24:18 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/09 21:02:29 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "return.h"
#include "libft.h"

t_error	ft_pwd(char **argv)
{
	char	*path;

	argv = (char **)argv;
	path = getcwd(NULL, 0);
	if (!path)
		return (ERROR);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	path = NULL;
	return (SCS);
}
