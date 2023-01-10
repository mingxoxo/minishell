/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:15:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/10 22:03:05 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "token.h"

int	*init_arr(size_t len)
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

static int	check_cust_idx(char *line)
{
	int			i;
	const char	symbol[12][3] = {"\"", "\'", "&&", "||", "(", ")", \
								"<<", "<", ">>", ">", "|", " "};
	const int	cust_idx[] = {50, 52, 41, 43, 30, 32, \
								21, 22, 23, 24, 10, 60};

	i = 0;
	while (i < 12)
	{
		if (ft_strncmp(line, (char *)(symbol[i]), ft_strlen(symbol[i])) == 0)
			return (cust_idx[i]);
		i++;
	}
	return (0);
}

void	fill_arr(char *line, int *arr)
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

static void	make_word(int *arr, int start, int end)
{
	int	i;

	i = start;
	while (i < end + 1)
	{
		arr[i] = 0;
		i++;
	}
}

void	handling_quote(char *line, int *arr, char c)
{
	char	*start;
	char	*one;
	char	*two;

	start = line;
	while (*start)
	{
		one = ft_strchr(start, c);
		if (!one)
			return ;
		two = ft_strchr(one + 1, c);
		if (!two)
		{
			arr[one - line] = 0;
			return ;
		}
		make_word(arr, one - line, two - line);
		start = two + 1;
	}
}
