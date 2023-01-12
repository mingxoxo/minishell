/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/11 19:49:10 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_tree.h"
#include "token.h"

void	preorder(t_tnode *node, int level, char *direction)
{
	t_token	*token;

	if (!node)
		return ;
	token = (t_token *)(node->content);
	if (!token)
		printf("level: %d d: %s NULL\n", level, direction);
	else
		printf("level: %d d: %s [%s]\n", level, direction, token->str);
	preorder(node->left, level + 1, "left");
	preorder(node->right, level + 1, "right");
}

void	inorder(t_tnode *node)
{
	if (!node)
		return ;
	inorder(node->left);
	printf("%s\n", (char *)(node->content));
	inorder(node->right);
}
