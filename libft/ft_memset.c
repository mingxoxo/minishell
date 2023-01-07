/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:04:16 by wonyang           #+#    #+#             */
/*   Updated: 2022/07/10 16:48:52 by wonyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	unsigned char	*dst;
	unsigned char	ch;
	size_t			i;

	dst = (unsigned char *)ptr;
	ch = (unsigned char)value;
	i = 0;
	while (i < len)
	{
		*dst = ch;
		dst++;
		i++;
	}
	return (ptr);
}
