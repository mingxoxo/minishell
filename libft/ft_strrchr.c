/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:41:45 by wonyang           #+#    #+#             */
/*   Updated: 2022/07/10 23:16:17 by wonyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	ch;
	char	*res;
	size_t	i;

	ch = (char)c;
	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			res = (char *)(str + i);
		i++;
	}
	if (str[i] == ch)
		res = (char *)(str + i);
	return (res);
}
