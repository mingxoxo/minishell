/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:38:04 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/11 20:23:02 by jeongmin         ###   ########.fr       */
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
	if (*node && is_root_symbol((*node)->content))
		set_rchild(*node, tree);
	else
		*node = tree;
	*lst = paren;
	return (SCS);
}

t_error	make_root(t_tnode **node, t_list *lst)
{
	t_tnode	*new;
	t_tnode	*root;

	new = init_node(lst->content);
	if (!new)
		return (ERROR);
	root = search_root(*node);
	if (root)
		set_lchild(new, root);
	*node = new;
	return (SCS);
}

t_error	make_t_io(t_tnode *node, t_list **lst)
{
	t_tnode	*new;
	t_tnode	*file;

	new = init_node((*lst)->content);
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
