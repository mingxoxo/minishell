/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 14:46:49 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ds_tree.h"

t_tnode	*init_node(void *content)
{
	t_tnode	*new;

	new = (t_tnode *)malloc(sizeof(t_tnode));
	if (!new)
		return (NULL);
	new->content = content;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	set_content(t_tnode *node, void *content)
{
	if (!node)
		return ;
	node->content = content;
}

void	set_lchild(t_tnode *node, t_tnode *left)
{
	if (node)
		node->left = left;
	if (left)
		left->parent = node;
}

void	set_rchild(t_tnode *node, t_tnode *right)
{
	if (node)
		node->right = right;
	if (right)
		right->parent = node;
}
