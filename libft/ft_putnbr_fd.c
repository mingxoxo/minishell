/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 05:03:34 by wonyang           #+#    #+#             */
/*   Updated: 2022/07/12 16:53:17 by wonyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	int_to_char(int n, int fd)
{
	char	c[12];
	int		idx;

	idx = 0;
	while (n > 0)
	{
		c[idx] = n % 10 + '0';
		idx++;
		n /= 10;
	}
	idx--;
	while (idx >= 0)
	{
		write(fd, &c[idx], 1);
		idx--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
	{
		n = n * -1;
		write(fd, "-", 1);
		int_to_char(n, fd);
	}
	else
		int_to_char(n, fd);
}
