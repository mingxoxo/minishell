/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:16:59 by wonyang           #+#    #+#             */
/*   Updated: 2022/07/10 20:05:35 by wonyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t len)
{
	const unsigned char	*p;
	unsigned char		ch;
	size_t				i;

	p = (const unsigned char *)ptr;
	ch = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		if (p[i] == ch)
			return ((void *)(p + i));
		i++;
	}
	return (0);
}
