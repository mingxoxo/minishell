/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:31:55 by wonyang           #+#    #+#             */
/*   Updated: 2022/07/09 14:50:50 by wonyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_length(long n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
	{
		n *= -1;
		count++;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	len;
	char	*res;
	long	num;

	num = (long)n;
	len = count_length(num);
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (res);
	i = len - 1;
	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	if (num == 0)
		res[0] = '0';
	while (num)
	{
		res[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	return (res);
}
