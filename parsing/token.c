/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:15:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/10 19:07:25 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "token.h"


static int	check_cust_idx(char *line)
{
	int			i;
	const char	symbol[12][3] = {"\"", "\'", "&&", "||", "(", ")", \
								"<<", "<", ">>", ">", "|", " "};
	const int	cust_idx[] = {60, 62, 51, 53, 40, 42, \
								31, 32, 33, 34, 20, 10};

	i = 0;
	while (i < 12)
	{
		if (ft_strncmp(line, (char *)(symbol[i]), ft_strlen(symbol[i])) == 0)
			return (cust_idx[i]);
		i++;
	}
	return (0);
}

static int	*init_arr(size_t len)
{
	int		*arr;
	size_t	i;

	arr = (int *)malloc(sizeof(int) * len);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = -1;
		i++;
	}
	return (arr);
}

static void	fill_arr(char *line, int *arr)
{
	int	i;
	int	cnt;
	int	cust_idx;

	while (*line)
	{
		cust_idx = check_cust_idx(line);
		cnt = cust_idx % 10 % 2 + 1;
		line += cnt;
		i = 0;
		while (i < cnt)
		{
			*arr = cust_idx;
			i++;
			arr++;
		}
	}
}

t_error	tokenization(char *line)
{
	int	*arr;

	arr = init_arr(ft_strlen(line));
	if (!arr)
		return (ERROR);
	fill_arr(line, arr);
	for (int i = 0; i < ft_strlen(line); i++)
		printf(" %d", arr[i]);
	printf("\n");
	free(arr);
	return (SCS);
}
