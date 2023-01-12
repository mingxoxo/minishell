/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:38:04 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/12 19:45:07 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

t_list	*check_end_node(t_list **lst)
{
	int		cnt;
	t_list	*end;

	end = *lst;
	if (!end)
		return (NULL);
	cnt = 1;
	while (end->next)
	{
		cnt += check_paren(end->next->content);
		if (cnt == 0)
			break ;
		end = end->next;
	}
	if (!(end->next))
		return (NULL);
	if (is_this_symbol(end->content, T_PAREN))
	{
		*lst = end;
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
