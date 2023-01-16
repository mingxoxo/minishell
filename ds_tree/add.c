/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/16 19:04:02 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_tree.h"

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
