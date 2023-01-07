/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:41:42 by wonyang           #+#    #+#             */
/*   Updated: 2022/07/12 16:49:24 by wonyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*now;
	t_list	*nxt;

	now = *lst;
	nxt = now->next;
	while (nxt)
	{
		ft_lstdelone(now, del);
		now = nxt;
		nxt = now->next;
	}
	ft_lstdelone(now, del);
	*lst = 0;
}
