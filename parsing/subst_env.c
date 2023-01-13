/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/13 23:32:42 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"
#include "minishell.h"

// substitute_env

extern t_global	g_var;

void	handling_envp(int *arr, int len)
{
	int	i;

	i = 1;
	while (i < len)
	{
		if (arr[i] == T_WORD && arr[i - 1] / 10 == T_DOLLER)
		{
			arr[i - 1] = T_DOLLER * 10 + 1;
			arr[i] = T_ENVP * 10;
		}
		else if (arr[i] == T_WORD && arr[i - 1] == T_ENVP * 10)
			arr[i] = T_ENVP * 10;
		i++;
	}
	i = 0;
	while (i < len)
	{
		if (arr[i] == T_DOLLER * 10)
			arr[i] = 0;
		i++;
	}
}

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
