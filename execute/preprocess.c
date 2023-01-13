/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:12:24 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/12 16:32:29 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ds_tree.h"
#include "token.h"
#include "libft.h"

static bool	is_cmd(t_tnode *node)
{
	t_token	*token;

	token = (t_token *)node->content;
	if (token->type == T_WORD)
		return (true);
	return (false);
}

static int	count_cmd_node(t_tnode *node)
{
	int	cnt;

	cnt = 0;
	if (is_cmd(node))
		return (1);
	cnt += count_cmd_node(node->left);
	cnt += count_cmd_node(node->right);
	return (cnt);
}

static void	cmd_preorder(t_tnode *node, t_tnode **cmd_list, int idx)
{
	if (is_cmd(node))
	{
		cmd_list[idx] = node;
		return ;
	}
	cmd_preorder(node->left, cmd_list, idx - 1);
	cmd_preorder(node->right, cmd_list, idx);
}

t_tnode	**make_cmd_list(t_tnode *root)
{
	t_tnode	**cmd_list;
	int		cmd_count;

	cmd_count = count_cmd_node(root);
	cmd_list = (t_tnode **)ft_calloc(cmd_count + 1, sizeof(t_tnode *));
	if (!cmd_list)
		return (NULL);
	cmd_preorder(root, cmd_list, cmd_count - 1);
	return (cmd_list);
}
