/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/11 18:10:46 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_tree.h"

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
	node->left = left;
	left->parent = node;
}

void	set_rchild(t_tnode *node, t_tnode *right)
{
	node->right = right;
	right->parent = node;
}
