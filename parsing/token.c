/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:15:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/10 19:59:16 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "token.h"

static void	print_arr(int *arr, char *line)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		printf(" %d", arr[i]);
		i++;
	}
	printf("\n");
}

t_error	tokenization(char *line)
{
	int		*arr;

	arr = init_arr(ft_strlen(line));
	if (!arr)
		return (ERROR);
	fill_arr(line, arr);
	print_arr(arr, line);
	handling_quote(line, arr, '\"');
	handling_quote(line, arr, '\'');
	print_arr(arr, line);
	free(arr);
	return (SCS);
}
