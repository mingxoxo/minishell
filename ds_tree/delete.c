/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/12 14:29:37 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_tree.h"

static t_pos	chk_position(t_tnode *node)
{
	t_tnode	*parent;

	parent = node->parent;
	if (parent == NULL)
		return (NONE);
	if (parent->left == node)
		return (LEFT);
	else if (parent->right == node)
		return (RIGHT);
	return (NONE);
}

void	del_node(t_tnode *node, void (*del)(void *))
{
	t_pos	pos;

	if (!node)
		return ;
	if (node->left || node->right)
	{
		printf("del_node error: node has child.");
		return ;
	}
	pos = chk_position(node);
	if (pos == LEFT)
		node->parent->left = NULL;
	else if (pos == RIGHT)
		node->parent->right = NULL;
	if (del)
		(*del)(node->content);
	free(node);
}

t_tnode	*clear_node(t_tnode *node, void (*del)(void *))
{
	if (!node)
		return (NULL);
	clear_node(node->left, del);
	clear_node(node->right, del);
	del_node(node, del);
	return (NULL);
}

void	*pop_node(t_tnode *node)
{
	void	*content;

	content = node->content;
	del_node(node, NULL);
	return (content);
}
