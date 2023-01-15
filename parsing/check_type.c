/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:38:04 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 22:35:17 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

bool	is_dsv_symbol(t_token *token)
{
	if (token == NULL || token->str == NULL)
		return (false);
	if (token->type == T_OPER || token->type == T_PIPE)
		return (true);
	return (false);
}

bool	is_this_symbol(t_token *token, t_ttype type)
{
	if (token == NULL || token->str == NULL)
		return (false);
	if (token->type == type)
		return (true);
	return (false);
}

int	check_paren(t_token *token)
{
	if (is_this_symbol(token, T_PAREN))
	{
		if (!token->str)
			return (0);
		if (ft_strcmp(token->str, "(") == 0)
			return (OPEN_PAREN);
		else if (ft_strcmp(token->str, ")") == 0)
			return (CLOSE_PAREN);
	}
	return (0);
}
