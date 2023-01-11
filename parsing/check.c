/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:38:04 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/11 20:14:44 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

bool	is_root_symbol(t_token *token)
{
	if (token == NULL)
		return (false);
	if (token->type == T_OPER || token->type == T_PIPE)
		return (true);
	return (false);
}

bool	is_this_symbol(t_token *token, t_ttype type)
{
	if (token == NULL)
		return (false);
	if (token->type == type)
		return (true);
	return (false);
}

t_list	*check_end_node(t_list *lst)
{
	t_list	*end;

	end = lst;
	while (end->next && !is_this_symbol(end->next->content, T_PAREN))
		end = end->next;
	if (end == lst)
		return (NULL);
	return (end);
}
