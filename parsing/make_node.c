/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:38:04 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/11 22:45:17 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

t_error	make_new_node(t_tnode **node)
{
	t_tnode	*new;

	new = init_node(NULL);
	if (!new)
		return (ERROR);
	if (*node)
		set_rchild(*node, new);
	*node = new;
	return (SCS);
}

t_error	make_t_paren(t_tnode **node, t_list **lst)
{
	t_tnode	*tree;
	t_list	*end;
	t_list	*paren;

	end = check_end_node((*lst)->next);
	if (!end)
		return (FAIL);
	paren = end->next;
	end->next = NULL;
	tree = make_tree((*lst)->next);
	end->next = paren;
	if (!tree)
		return (ERROR);
	if (*node && is_dsv_symbol((*node)->content))
		set_rchild(*node, tree);
	else
		*node = tree;
	*lst = paren;
	return (SCS);
}

t_error	make_dsv_node(t_tnode **node, t_list *lst)
{
	t_tnode	*new;
	t_tnode	*parent;

	new = init_node(lst->content);
	if (!new)
		return (ERROR);
	parent = check_parent(*node, lst->content);
	if (parent)
	{
		set_lchild(new, parent->right);
		set_rchild(parent, new);
	}
	else
		set_lchild(new, check_root(*node));
	*node = new;
	return (SCS);
}

t_error	make_t_io(t_tnode *node, t_list **lst)
{
	t_tnode	*new;
	t_tnode	*file;

	new = init_node((*lst)->content);
	if (!((*lst)->next))
	{
		free(new);
		return (FAIL);
	}
	(*lst) = (*lst)->next;
	file = init_node((*lst)->content);
	if (!new || !file)
	{
		free(new);
		free(file);
		return (ERROR);
	}
	while (node->right)
		node = node->right;
	set_rchild(node, new);
	set_lchild(new, file);
	return (SCS);
}

t_error	make_t_word(t_tnode *node, t_list *lst)
{
	t_tnode	*new;

	if (node->content == NULL)
	{
		node->content = lst->content;
		return (SCS);
	}
	new = init_node(lst->content);
	if (!new)
		return (ERROR);
	while (node->left)
		node = node->left;
	set_lchild(node, new);
	return (SCS);
}
