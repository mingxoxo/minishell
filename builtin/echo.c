/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:35:35 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/06 21:20:32 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"

// ** returns
// valid option : true
// invalid option : false
static bool	valid_option(char *str)
{
	int	i;

	if (!str || *str != '-' || str[1] != 'n')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	print_argument(char **argv, int start_idx)
{
	int	i;

	i = start_idx;
	while (argv[i])
	{
		if (i != start_idx)
			ft_putchar_fd(' ', STDIN_FILENO);
		ft_putstr_fd(argv[i], STDIN_FILENO);
		i++;
	}
}

int	ft_echo(char **argv)
{
	char	*option;

	if (!argv || !(*argv))
	{
		printf("ft_echo argument error!\n");
		return (-1);
	}
	if (valid_option(argv[1]) == true)
		print_argument(argv, 2);
	else
	{
		print_argument(argv, 1);
		ft_putchar_fd('\n', STDIN_FILENO);
	}
	return (0);
}
