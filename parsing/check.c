/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:38:04 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/12 15:12:23 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

bool	is_dsv_symbol(t_token *token)
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

t_list	*check_end_node(t_list **lst)
{
	t_list	*end;

	end = *lst;
	if (!end)
		return (NULL);
	while (end->next && !is_this_symbol(end->next->content, T_PAREN))
		end = end->next;
	if (!(end->next))
		return (NULL);
	if (is_this_symbol(end->content, T_PAREN))
	{
		*lst = (*lst)->next;
		return (NULL);
	}
	return (end);
}

t_tnode	*check_parent(t_tnode *node, t_token *token)
{
	t_token	*parent;

	while (node)
	{
		parent = (t_token *)(node->content);
		if (parent->type > token->type)
			return (node);
		node = node->parent;
	}
	return (node);
}

t_tnode	*check_root(t_tnode *node)
{
	if (!node)
		return (NULL);
	while (node->parent)
		node = node->parent;
	return (node);
}
