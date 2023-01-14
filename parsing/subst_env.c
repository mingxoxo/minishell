/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 18:29:54 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// substitute_env

static t_error	cmd_subst_env(t_tnode *node)
{
	while (node)
	{
		if (env_first_step(node->content) == ERROR)
			return (ERROR);
		node = node->left;
	}
	return (SCS);
}

t_error	subst_env(t_tnode *node)
{
	t_error	errno;

	if (!node)
		return (SCS);
	if (is_this_symbol(node->content, T_WORD))
		return (cmd_subst_env(node));
	errno = subst_env(node->left);
	errno = subst_env(node->right);
	return (errno);
}
