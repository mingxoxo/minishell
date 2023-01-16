/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/16 17:06:55 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// substitute

static bool	is_envp_in_cmd(t_tnode *node)
{
	while (node)
	{
		if (ft_strchr(((t_token *)(node->content))->str, '$'))
			return (true);
		node = node->left;
	}
	return (false);
}

static bool	is_wildcard_in_cmd(t_tnode *node)
{
	while (node)
	{
		if (ft_strchr(((t_token *)(node->content))->str, '*'))
			return (true);
		node = node->left;
	}
	return (false);
}

t_error	subst(t_tnode *node)
{
	t_error	errno;

	if (!node)
		return (SCS);
	if (is_this_symbol(node->content, T_WORD))
	{
		if (is_envp_in_cmd(node) && cmd_subst_env(node, node) == ERROR)
			return (ERROR);
		if (r_file_subst_env(node) == ERROR)
			return (ERROR);
		if (is_wildcard_in_cmd(node) && subst_wildcard(node) == ERROR)
			return (ERROR);
		return (SCS);
	}
	errno = subst(node->left);
	errno = subst(node->right);
	return (errno);
}
