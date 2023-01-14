/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 23:02:36 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// substitute_env

static char	*strjoin_cmd(char *cache, t_token *token)
{
	char	*new;
	char	*new2;

	new = ft_strjoin(cache, " ");
	if (!new)
		return (NULL);
	new2 = ft_strjoin(new, token->str);
	if (!new2)
	{
		free(new);
		return (NULL);
	}
	return (new2);
}

static t_error	cmd_subst_env(t_tnode *node, t_tnode *cmd)
{
	char	*new;
	char	*cache;

	cache = ft_strdup("");
	if (!cache)
		return (ERROR);
	while (node)
	{
		if (env_first_step(node->content) == ERROR)
			return (ERROR);
		new = strjoin_cmd(cache, node->content);
		if (!new)
		{
			free(cache);
			return (ERROR);
		}
		cache = new;
		node = node->left;
	}
	if (env_second_step(cache, cmd) == ERROR)
	{
		free(cache);
		return (ERROR);
	}
	return (SCS);
}

t_error	subst_env(t_tnode *node)
{
	t_error	errno;

	if (!node)
		return (SCS);
	if (is_this_symbol(node->content, T_WORD))
		return (cmd_subst_env(node, node));
	errno = subst_env(node->left);
	errno = subst_env(node->right);
	return (errno);
}
