/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:52:16 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/12 22:18:32 by jeongmin         ###   ########.fr       */
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

static bool	is_correct_io(t_list *lst)
{
	while (lst)
	{
		if (is_this_symbol(lst->content, T_IO))
		{
			lst = lst->next;
			if (!lst || !is_this_symbol(lst->content, T_WORD))
				return (false);
		}
		lst = lst->next;
	}
	return (true);
}

bool	is_correct_syntax(t_list *lst)
{
	if (!is_correct_paren(lst))
	{
		ft_putendl_fd("bash: syntax error near unexpected token `)'", 2);
		return (false);
	}
	if (!is_correct_io(lst))
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		return (false);
	}
	return (true);
}
