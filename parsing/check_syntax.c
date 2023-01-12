/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:52:16 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/12 22:01:38 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

static bool	is_correct_paren(t_list *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		cnt += check_paren(lst->content);
		if (cnt < 0)
			return (false);
		lst = lst->next;
	}
	if (cnt != 0)
		return (false);
	return (true);
}

bool	is_correct_syntax(t_list *lst)
{
	if (!is_correct_paren(lst))
		return (false);
	return (true);
}
