/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:15:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 17:09:11 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	count_len(char *line, int *arr, int i)
{
	size_t	len;

	i++;
	len = 1;
	while (line[i] && arr[i - 1] == arr[i])
	{
		len++;
		i++;
	}
	return (len);
}

void	fill_arr(char *line, int *arr, int (*chk_idx)(char *))
{
	int	i;
	int	cnt;
	int	cust_idx;

	while (*line)
	{
		cust_idx = (*chk_idx)(line);
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

void	make_word_arr(int *arr, int start, int end)
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
		make_word_arr(arr, one - line, two - line);
		start = two + 1;
	}
}
