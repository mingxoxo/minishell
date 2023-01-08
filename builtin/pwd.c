/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:24:18 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/08 16:07:50 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/return.h"
#include "../libft/libft.h"

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
