/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syatax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:45:48 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/12 18:44:10 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

int	chk_paren(t_token *token)
{
	if (is_this_symbol(token, T_PAREN))
	{
		if (!token->str)
			return (0);
		if (ft_strcmp(token->str, "(") == 0)
			return (1);
		else if (ft_strcmp(token->str, ")") == 0)
			return (-1);
	}
	return (0);
}

static bool	is_correct_paren(t_list *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		cnt += chk_paren(lst->content);
		if (cnt < 0)
			return (false);
	}
	if (cnt != 0)
		return (false);
	return (true);
}

bool	is_correct_syntax(t_list *lst)
{
	if (!is_correct_paren)
		return (false);
	return (true);
}
