/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 14:46:49 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ds_tree.h"

t_tnode	*add_lchild(t_tnode *node, void *content)
{
	t_tnode	*left;

	left = init_node(content);
	if (!left)
		return (NULL);
	set_lchild(left, node->left);
	set_lchild(node, left);
	return (left);
}

t_tnode	*add_rchild(t_tnode *node, void *content)
{
	t_tnode	*right;

	right = init_node(content);
	if (!right)
		return (NULL);
	set_rchild(right, node->right);
	set_rchild(node, right);
	return (right);
}
