/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/06 22:12:08 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_tree.h"

void	preorder(t_tnode *node)
{
	if (!node)
		return ;
	printf("%s\n", (char *)(node->content));
	preorder(node->left);
	preorder(node->right);
}

void	inorder(t_tnode *node)
{
	if (!node)
		return ;
	inorder(node->left);
	printf("%s\n", (char *)(node->content));
	inorder(node->right);
}
