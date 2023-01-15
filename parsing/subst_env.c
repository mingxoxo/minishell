/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/15 17:32:37 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// substitute_env

static char	*strjoin_cmd(t_tnode *node, size_t len)
{
	char	*new;

	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (node)
	{
		ft_strlcat(new, " ", len + 1);
		ft_strlcat(new, ((t_token *)(node->content))->str, len + 1);
		node = node->left;
	}
	return (new);
}

static t_error	r_file_subst_env(t_tnode *node)
{
	node = node->right;
	while (node)
	{
		if (ft_strcmp(((t_token *)(node->content))->str, "<<") == 0)
		{
			node = node->right;
			continue ;
		}
		if (env_first_step(node->left->content) == ERROR)
			return (ERROR);
		node = node->right;
	}
	return (SCS);
}

static t_error	cmd_subst_env(t_tnode *node, t_tnode *cmd)
{
	size_t	len;
	char	*line;

	len = 0;
	while (node)
	{
		if (env_first_step(node->content) == ERROR)
			return (ERROR);
		len += ft_strlen(((t_token *)(node->content))->str) + 1;
		node = node->left;
	}
	line = strjoin_cmd(cmd, len);
	if (!line)
		return (ERROR);
	if (env_second_step(line, cmd) == ERROR)
	{
		free(line);
		return (ERROR);
	}
	free(line);
	return (SCS);
}

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

t_error	subst_env(t_tnode *node)
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
		return (SCS);
	}
	errno = subst_env(node->left);
	errno = subst_env(node->right);
	return (errno);
}
